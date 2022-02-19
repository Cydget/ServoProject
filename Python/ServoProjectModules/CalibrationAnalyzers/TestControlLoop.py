from ServoProjectModules.CalibrationAnalyzers.Helper import *

def createGuiBox(parent, nodeNr, getPortFun, configFilePath, configClassName, advancedMode):
    calibrationBox = Gtk.Box(orientation=Gtk.Orientation.VERTICAL)
    calibrationBox.set_margin_start(40)
    calibrationBox.set_margin_bottom(100)

    controlSpeedScale = GuiFunctions.creatHScale(14, 0, 100, 1, getLowLev=True)
    controlSpeedScale = GuiFunctions.addTopLabelTo('<b>Control speed</b>', controlSpeedScale[0]), controlSpeedScale[1]
    calibrationBox.pack_start(controlSpeedScale[0], False, False, 0)

    if advancedMode == True:
        velControlSpeedScale = GuiFunctions.creatHScale(14 * 4, 0, 100 * 4, 4, getLowLev=True)
        velControlSpeedScale = GuiFunctions.addTopLabelTo('<b>Velocity control speed</b>', velControlSpeedScale[0]), velControlSpeedScale[1]
        calibrationBox.pack_start(velControlSpeedScale[0], False, False, 0)

        filterSpeedScale = GuiFunctions.creatHScale(14 * 32, 0, 100 * 32, 32, getLowLev=True)
        filterSpeedScale = GuiFunctions.addTopLabelTo('<b>Filter speed</b>', filterSpeedScale[0]), filterSpeedScale[1]
        calibrationBox.pack_start(filterSpeedScale[0], False, False, 0)

    backlashControlSpeedScale = GuiFunctions.creatHScale(0, 0, 50, 1, getLowLev=True)
    backlashControlSpeedScale = GuiFunctions.addTopLabelTo('<b>Backlash control speed</b>', backlashControlSpeedScale[0]), backlashControlSpeedScale[1]
    calibrationBox.pack_start(backlashControlSpeedScale[0], False, False, 0)

    refVel = 0.2
    refPos = 0.0

    refVelScale = GuiFunctions.creatHScale(refVel, 0, 1.0, 0.01, getLowLev=True)
    refVelScale = GuiFunctions.addTopLabelTo('<b>Max Velocity</b>\n in radians per second', refVelScale[0]), refVelScale[1]

    refPosScale = GuiFunctions.creatHScale(refPos, -1.0, 1.0, 0.01, getLowLev=True)
    refPosScale = GuiFunctions.addTopLabelTo('<b>Set position offset</b>\n in radians', refPosScale[0]), refPosScale[1]

    startButton = GuiFunctions.createButton('Start test', getLowLev=True)

    statusLabel = GuiFunctions.createLabel(f'Position: - (start offset: -)\n'
                        f'Velocity: -\n'
                        f'Error at output: -\n'
                        f'Error at motor: -\n'
                        f'control signal: -\n'
                        f'Loop time: -')

    calibrationBox.pack_start(refVelScale[0], False, False, 0)
    calibrationBox.pack_start(refPosScale[0], False, False, 0)
    calibrationBox.pack_start(startButton[0], False, False, 0)
    calibrationBox.pack_start(statusLabel, False, False, 0)
    calibrationBox.show_all()

    threadMutex = threading.Lock()

    def onRefVelScaleChange(widget):
        nonlocal refVel
        with threadMutex:
            refVel = widget.get_value()

    def onRefPosScaleChange(widget):
        nonlocal refPos
        with threadMutex:
            refPos = widget.get_value()

    refVelScale[1].connect('value-changed', onRefVelScaleChange)
    refPosScale[1].connect('value-changed', onRefPosScaleChange)

    def updateStatusLabel(string):
        statusLabel.set_label(string)

    def resetGuiAfterCalibration():
        startButton[1].set_label('Start test')
        startButton[1].set_sensitive(True)
        controlSpeedScale[1].set_sensitive(True)
        if advancedMode == True:
            velControlSpeedScale[1].set_sensitive(True)
            filterSpeedScale[1].set_sensitive(True)

        backlashControlSpeedScale[1].set_sensitive(True)
        refPosScale[1].set_value(0.0)

    runThread = False

    def plotData(data):
        dialog = Gtk.MessageDialog(
                transient_for=parent,
                flags=0,
                message_type=Gtk.MessageType.INFO,
                buttons=Gtk.ButtonsType.YES_NO,
                text='Test done',
        )
        dialog.format_secondary_text(
            "Do you want to plot the recorded data?"
        )
        response = dialog.run()
        dialog.destroy()

        if response == Gtk.ResponseType.YES:
            time = data[:, 0] - data[0, 0]
            fig = plt.figure(1)
            fig.suptitle('Position')
            plt.plot(time, data[:, 8], 'r')
            plt.plot(time, data[:, 1], 'g')

            fig = plt.figure(2)
            fig.suptitle('Velocity')
            plt.plot(time, data[:, 2])

            fig = plt.figure(3)
            fig.suptitle('Error at output')
            plt.plot(time, data[:, 3])

            fig = plt.figure(4)
            fig.suptitle('Error at motor')
            plt.plot(time, data[:, 4])

            fig = plt.figure(5)
            fig.suptitle('Control signal')
            plt.plot(time, data[:, 5])

            fig = plt.figure(6)
            fig.suptitle('Control signal over motor position')
            plt.plot(np.array(data[:, 6]), data[:, 5], 'g+')

            plt.show()

    def startTestRun(nodeNr, port):
        nonlocal runThread

        controlSpeed = int(controlSpeedScale[1].get_value())
        velControlSpeed = controlSpeed * 4
        filterSpeed = controlSpeed * 32
        if advancedMode == True:
            velControlSpeed = int(round(velControlSpeedScale[1].get_value() / 4.0)) * 4
            velControlSpeedScale[1].set_value(velControlSpeed)
            filterSpeed = int(round(filterSpeedScale[1].get_value() / 32.0)) * 32
            filterSpeedScale[1].set_value(filterSpeed)
        backlashControlSpeed = int(backlashControlSpeedScale[1].get_value())

        def initFun(robot):
            robot.servoArray[0].setControlSpeed(controlSpeed, velControlSpeed, filterSpeed)
            robot.servoArray[0].setBacklashControlSpeed(backlashControlSpeed, 3.0, 0.0)

        with createRobot(nodeNr, port, dt=0.018, initFunction=initFun) as robot:
            t = 0.0
            doneRunning = False

            robot.servoArray[0].getPosition(False)
            posOffset = robot.servoArray[0].getPosition()
            moveHandler = SmoothMoveHandler(posOffset, 0.4)

            def sendCommandHandlerFunction(dt, robot):
                servo = robot.servoArray[0]

                with threadMutex:
                    moveHandler.set(refPos + posOffset, refVel)

                p, v = moveHandler.getNextRef(dt)
                servo.setReference(p, v, 0)

            out = []

            def readResultHandlerFunction(dt, robot):
                nonlocal t
                nonlocal doneRunning

                t += dt

                stop = False
                with threadMutex:
                    if runThread == False:
                        stop = True

                if stop or parent.isClosed:
                    robot.removeHandlerFunctions()
                    doneRunning = True
                    return

                servo = robot.servoArray[0]
                p = servo.getPosition(True)
                v = servo.getVelocity()
                u = servo.getControlSignal()
                error = servo.getControlError(True)
                motorError = servo.getControlError(False)
                optData = servo.getOpticalEncoderChannelData()
                out.append([time.time(), p, v,
                        error,
                        motorError,
                        u,
                        optData.minCostIndex,
                        optData.minCost,
                        refPos + posOffset])

                GLib.idle_add(updateStatusLabel, f'Position: {p - posOffset:0.4f} (start offset: {posOffset:0.2f})\n'
                        f'Velocity: {v:0.4f}\n'
                        f'Error at output: {error:0.4f}\n'
                        f'Error at motor: {motorError:0.4f}\n'
                        f'control signal: {u:0.4f}\n'
                        f'Loop time: {servo.getLoopTime()}')

            robot.setHandlerFunctions(sendCommandHandlerFunction, readResultHandlerFunction);

            while not doneRunning:
                if not robot.isAlive():
                    runThread = False
                    break
                time.sleep(0.1)

            robot.shutdown()

            data = np.array(out)
            GLib.idle_add(plotData, data)

        GLib.idle_add(resetGuiAfterCalibration)

    testThread = None

    def onStartTest(widget):
        nonlocal testThread
        nonlocal runThread

        if widget.get_label() == 'Start test':
            widget.set_label('Stop test')

            controlSpeedScale[1].set_sensitive(False)
            if advancedMode == True:
                velControlSpeedScale[1].set_sensitive(False)
                filterSpeedScale[1].set_sensitive(False)
            backlashControlSpeedScale[1].set_sensitive(False)

            calibrationBox.show_all()

            with threadMutex:
                runThread = True
            testThread = threading.Thread(target=startTestRun, args=(nodeNr, getPortFun(),))
            testThread.start()
        else:
            with threadMutex:
                runThread = False
            testThread.join()

    startButton[1].connect('clicked', onStartTest)

    return calibrationBox
