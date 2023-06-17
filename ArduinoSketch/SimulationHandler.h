#ifndef SIMULATION_HANDLER_H
#define SIMULATION_HANDLER_H

#include <ArduinoEigenDense.h>
#include "AdcHandler.h"
#include "OpticalEncoderHandler.h"
#include "ResistiveEncoderHandler.h"
#include "PwmHandler.h"

class SimulationHandler
{
public:
    constexpr static std::array<uint16_t, 2048> aVec = {5271, 5258, 5246, 5234, 5223, 5213, 5202, 5190, 5178, 5167, 5156, 5146, 5135, 5124, 5112, 5104, 5095, 5085, 5074, 5062, 5050, 5045, 5039, 5029, 5019, 5010, 5001, 4991, 4981, 4975, 4969, 4957, 4945, 4939, 4934, 4927, 4921, 4910, 4900, 4893, 4885, 4877, 4869, 4861, 4852, 4844, 4836, 4831, 4825, 4817, 4808, 4802, 4796, 4786, 4777, 4772, 4768, 4762, 4757, 4748, 4738, 4730, 4722, 4716, 4710, 4704, 4698, 4695, 4692, 4682, 4673, 4667, 4661, 4655, 4649, 4644, 4639, 4634, 4629, 4622, 4614, 4607, 4600, 4595, 4590, 4580, 4569, 4554, 4538, 4534, 4529, 4524, 4518, 4515, 4512, 4504, 4495, 4484, 4473, 4467, 4461, 4449, 4437, 4429, 4422, 4414, 4407, 4399, 4391, 4387, 4382, 4375, 4368, 4363, 4359, 4356, 4353, 4344, 4335, 4330, 4325, 4317, 4309, 4304, 4299, 4294, 4290, 4284, 4279, 4273, 4268, 4265, 4262, 4255, 4249, 4247, 4244, 4242, 4239, 4235, 4231, 4228, 4225, 4222, 4219, 4216, 4213, 4210, 4207, 4200, 4192, 4187, 4182, 4180, 4177, 4173, 4169, 4166, 4163, 4161, 4158, 4156, 4155, 4151, 4147, 4141, 4136, 4134, 4132, 4128, 4125, 4121, 4117, 4115, 4113, 4109, 4105, 4102, 4100, 4094, 4087, 4085, 4082, 4079, 4076, 4074, 4073, 4072, 4071, 4070, 4069, 4067, 4064, 4064, 4065, 4062, 4060, 4058, 4055, 4053, 4050, 4050, 4049, 4046, 4042, 4040, 4038, 4036, 4034, 4030, 4026, 4024, 4022, 4019, 4016, 4014, 4012, 4010, 4008, 4004, 4001, 3998, 3995, 3992, 3989, 3988, 3987, 3985, 3982, 3981, 3980, 3978, 3976, 3976, 3975, 3974, 3972, 3970, 3969, 3967, 3966, 3966, 3965, 3964, 3963, 3962, 3960, 3960, 3960, 3959, 3958, 3958, 3958, 3958, 3959, 3958, 3957, 3959, 3960, 3959, 3958, 3959, 3960, 3960, 3960, 3961, 3963, 3964, 3965, 3966, 3966, 3967, 3968, 3970, 3973, 3972, 3971, 3973, 3975, 3975, 3975, 3977, 3980, 3981, 3981, 3983, 3985, 3985, 3985, 3986, 3987, 3990, 3992, 3993, 3994, 3996, 3997, 4000, 4004, 4006, 4008, 4010, 4012, 4012, 4013, 4017, 4020, 4022, 4023, 4023, 4023, 4025, 4028, 4030, 4032, 4036, 4040, 4041, 4042, 4043, 4045, 4047, 4049, 4051, 4054, 4054, 4054, 4059, 4063, 4064, 4065, 4070, 4074, 4075, 4076, 4076, 4077, 4081, 4085, 4087, 4089, 4091, 4092, 4094, 4096, 4099, 4102, 4102, 4103, 4106, 4110, 4112, 4115, 4118, 4122, 4123, 4125, 4128, 4131, 4131, 4132, 4136, 4141, 4144, 4147, 4147, 4148, 4152, 4155, 4156, 4156, 4161, 4165, 4171, 4176, 4179, 4181, 4185, 4189, 4192, 4194, 4198, 4202, 4208, 4213, 4212, 4212, 4213, 4214, 4218, 4222, 4227, 4232, 4234, 4235, 4239, 4243, 4249, 4254, 4254, 4253, 4259, 4264, 4266, 4268, 4268, 4269, 4274, 4278, 4281, 4283, 4288, 4293, 4297, 4300, 4301, 4302, 4308, 4313, 4317, 4321, 4324, 4327, 4330, 4333, 4339, 4345, 4349, 4354, 4362, 4370, 4376, 4383, 4387, 4392, 4396, 4401, 4407, 4413, 4419, 4424, 4430, 4435, 4441, 4447, 4451, 4456, 4462, 4468, 4477, 4486, 4492, 4499, 4503, 4508, 4515, 4522, 4526, 4530, 4537, 4543, 4550, 4556, 4565, 4574, 4579, 4584, 4590, 4595, 4602, 4608, 4617, 4626, 4635, 4645, 4649, 4654, 4661, 4668, 4674, 4680, 4686, 4693, 4700, 4707, 4715, 4722, 4730, 4737, 4744, 4750, 4760, 4771, 4780, 4789, 4796, 4804, 4814, 4825, 4834, 4843, 4852, 4861, 4868, 4875, 4882, 4889, 4896, 4903, 4911, 4919, 4924, 4929, 4937, 4945, 4956, 4966, 4976, 4985, 4995, 5005, 5015, 5025, 5039, 5052, 5062, 5072, 5086, 5100, 5109, 5119, 5133, 5147, 5166, 5186, 5193, 5200, 5212, 5225, 5237, 5250, 5263, 5276, 5291, 5307, 5317, 5328, 5341, 5354, 5371, 5388, 5397, 5406, 5417, 5429, 5443, 5458, 5468, 5478, 5487, 5496, 5503, 5511, 5520, 5530, 5542, 5553, 5567, 5581, 5590, 5599, 5620, 5640, 5650, 5659, 5677, 5694, 5709, 5723, 5741, 5760, 5769, 5778, 5793, 5807, 5816, 5825, 5838, 5851, 5868, 5885, 5897, 5909, 5918, 5927, 5944, 5961, 5973, 5985, 6004, 6022, 6038, 6053, 6074, 6095, 6110, 6124, 6138, 6153, 6165, 6178, 6193, 6209, 6226, 6243, 6255, 6268, 6290, 6312, 6328, 6344, 6368, 6392, 6410, 6429, 6454, 6479, 6499, 6519, 6533, 6546, 6561, 6577, 6594, 6612, 6626, 6641, 6657, 6673, 6693, 6713, 6726, 6738, 6759, 6780, 6795, 6811, 6827, 6842, 6864, 6886, 6895, 6904, 6922, 6941, 6956, 6972, 6985, 6998, 7010, 7022, 7032, 7042, 7055, 7068, 7086, 7104, 7126, 7147, 7169, 7190, 7203, 7216, 7233, 7250, 7267, 7284, 7302, 7321, 7338, 7355, 7373, 7391, 7410, 7429, 7443, 7458, 7473, 7488, 7511, 7533, 7553, 7573, 7590, 7607, 7628, 7649, 7671, 7692, 7708, 7723, 7741, 7760, 7778, 7796, 7812, 7828, 7845, 7861, 7881, 7901, 7919, 7936, 7956, 7976, 7999, 8021, 8049, 8076, 8096, 8115, 8135, 8154, 8174, 8194, 8219, 8243, 8263, 8282, 8308, 8333, 8361, 8388, 8414, 8440, 8462, 8483, 8503, 8522, 8543, 8565, 8596, 8628, 8648, 8667, 8697, 8728, 8744, 8761, 8782, 8803, 8828, 8852, 8875, 8898, 8916, 8933, 8950, 8967, 8987, 9007, 9026, 9046, 9075, 9104, 9127, 9150, 9169, 9187, 9216, 9244, 9271, 9297, 9323, 9349, 9368, 9388, 9406, 9423, 9448, 9473, 9481, 9490, 9507, 9525, 9543, 9562, 9577, 9593, 9614, 9634, 9653, 9672, 9690, 9708, 9730, 9752, 9771, 9790, 9809, 9828, 9848, 9868, 9891, 9915, 9926, 9938, 9953, 9967, 9981, 10028, 10047, 10066, 10085, 10104, 10118, 10132, 10150, 10169, 10178, 10187, 10209, 10231, 10252, 10274, 10293, 10312, 10333, 10354, 10371, 10388, 10408, 10429, 10438, 10447, 10463, 10479, 10498, 10517, 10528, 10539, 10551, 10563, 10584, 10606, 10620, 10634, 10649, 10665, 10686, 10707, 10722, 10737, 10752, 10767, 10781, 10794, 10805, 10815, 10827, 10839, 10853, 10866, 10881, 10897, 10911, 10925, 10943, 10961, 10975, 10989, 11002, 11014, 11032, 11049, 11064, 11079, 11091, 11103, 11116, 11130, 11147, 11165, 11175, 11184, 11202, 11220, 11230, 11240, 11254, 11268, 11282, 11295, 11310, 11324, 11344, 11365, 11375, 11385, 11391, 11397, 11408, 11419, 11431, 11444, 11455, 11466, 11476, 11486, 11495, 11503, 11513, 11523, 11536, 11550, 11562, 11575, 11588, 11600, 11614, 11627, 11641, 11654, 11664, 11674, 11698, 11721, 11737, 11752, 11766, 11780, 11789, 11799, 11814, 11829, 11843, 11857, 11870, 11882, 11892, 11902, 11913, 11923, 11936, 11948, 11959, 11970, 11982, 11995, 12002, 12010, 12024, 12038, 12055, 12072, 12081, 12089, 12101, 12112, 12126, 12140, 12156, 12172, 12182, 12193, 12207, 12220, 12229, 12238, 12250, 12263, 12275, 12287, 12300, 12312, 12325, 12337, 12348, 12358, 12370, 12383, 12395, 12408, 12422, 12436, 12449, 12461, 12475, 12488, 12498, 12508, 12516, 12524, 12549, 12575, 12584, 12593, 12606, 12620, 12633, 12646, 12655, 12664, 12671, 12679, 12688, 12697, 12710, 12723, 12734, 12745, 12755, 12765, 12773, 12781, 12786, 12791, 12799, 12808, 12815, 12823, 12833, 12843, 12855, 12868, 12882, 12896, 12905, 12915, 12925, 12935, 12948, 12961, 12972, 12982, 12995, 13007, 13022, 13036, 13047, 13058, 13075, 13092, 13098, 13104, 13114, 13125, 13136, 13148, 13158, 13168, 13180, 13191, 13202, 13213, 13223, 13233, 13242, 13251, 13261, 13270, 13279, 13288, 13298, 13307, 13319, 13331, 13339, 13348, 13358, 13368, 13376, 13384, 13393, 13402, 13410, 13419, 13430, 13440, 13453, 13465, 13474, 13483, 13489, 13496, 13505, 13515, 13524, 13532, 13536, 13540, 13547, 13554, 13560, 13566, 13574, 13581, 13587, 13593, 13601, 13609, 13611, 13613, 13619, 13624, 13630, 13635, 13643, 13650, 13659, 13668, 13672, 13676, 13680, 13684, 13691, 13698, 13702, 13706, 13712, 13718, 13720, 13723, 13728, 13734, 13736, 13739, 13741, 13743, 13749, 13754, 13756, 13759, 13760, 13762, 13768, 13773, 13776, 13778, 13780, 13782, 13785, 13788, 13793, 13797, 13800, 13804, 13809, 13814, 13819, 13824, 13828, 13831, 13836, 13841, 13846, 13852, 13856, 13860, 13862, 13865, 13867, 13870, 13873, 13875, 13878, 13881, 13883, 13885, 13888, 13891, 13895, 13899, 13901, 13903, 13904, 13905, 13908, 13910, 13912, 13914, 13916, 13918, 13918, 13917, 13918, 13919, 13919, 13920, 13920, 13920, 13922, 13924, 13925, 13925, 13927, 13929, 13932, 13935, 13935, 13936, 13937, 13938, 13938, 13939, 13939, 13939, 13940, 13941, 13942, 13943, 13943, 13943, 13944, 13944, 13947, 13949, 13949, 13950, 13951, 13953, 13954, 13955, 13955, 13955, 13957, 13959, 13961, 13962, 13962, 13963, 13964, 13965, 13965, 13966, 13967, 13969, 13969, 13970, 13971, 13971, 13972, 13973, 13976, 13979, 13980, 13981, 13981, 13982, 13983, 13984, 13986, 13988, 13989, 13991, 13991, 13992, 13996, 13999, 14003, 14007, 14010, 14013, 14015, 14017, 14019, 14022, 14022, 14023, 14026, 14029, 14029, 14029, 14031, 14033, 14034, 14035, 14036, 14037, 14040, 14043, 14047, 14051, 14054, 14057, 14058, 14060, 14062, 14065, 14067, 14070, 14070, 14071, 14072, 14074, 14074, 14075, 14075, 14075, 14076, 14076, 14076, 14076, 14078, 14079, 14079, 14079, 14079, 14080, 14079, 14078, 14079, 14079, 14079, 14079, 14078, 14078, 14078, 14078, 14078, 14078, 14077, 14075, 14075, 14074, 14069, 14063, 14059, 14056, 14051, 14046, 14044, 14042, 14039, 14037, 14035, 14033, 14030, 14027, 14027, 14026, 14023, 14019, 14016, 14012, 14011, 14010, 14005, 13999, 13996, 13993, 13988, 13983, 13980, 13977, 13976, 13974, 13971, 13968, 13967, 13966, 13962, 13959, 13956, 13954, 13951, 13949, 13946, 13943, 13940, 13937, 13933, 13929, 13927, 13924, 13922, 13920, 13917, 13914, 13912, 13910, 13907, 13905, 13902, 13900, 13897, 13894, 13891, 13889, 13886, 13883, 13880, 13877, 13870, 13864, 13859, 13853, 13849, 13844, 13839, 13834, 13829, 13824, 13819, 13814, 13812, 13810, 13808, 13805, 13805, 13804, 13803, 13801, 13798, 13794, 13790, 13787, 13782, 13778, 13775, 13773, 13771, 13768, 13763, 13758, 13754, 13751, 13742, 13734, 13730, 13726, 13720, 13713, 13710, 13706, 13703, 13699, 13697, 13694, 13690, 13687, 13682, 13676, 13671, 13666, 13663, 13659, 13654, 13649, 13643, 13637, 13632, 13628, 13623, 13617, 13614, 13610, 13607, 13604, 13600, 13597, 13594, 13591, 13589, 13586, 13582, 13577, 13575, 13572, 13568, 13564, 13557, 13551, 13545, 13540, 13536, 13532, 13526, 13521, 13515, 13508, 13498, 13488, 13480, 13472, 13462, 13452, 13443, 13435, 13428, 13421, 13411, 13401, 13395, 13388, 13382, 13376, 13370, 13363, 13358, 13353, 13347, 13341, 13333, 13325, 13318, 13311, 13304, 13298, 13290, 13282, 13275, 13269, 13261, 13254, 13247, 13240, 13233, 13227, 13220, 13214, 13209, 13204, 13199, 13194, 13191, 13188, 13182, 13177, 13170, 13164, 13157, 13150, 13144, 13138, 13129, 13119, 13110, 13100, 13092, 13084, 13077, 13070, 13064, 13058, 13048, 13037, 13026, 13014, 13004, 12993, 12979, 12964, 12959, 12954, 12944, 12933, 12921, 12909, 12900, 12891, 12878, 12864, 12852, 12841, 12833, 12826, 12815, 12803, 12796, 12790, 12779, 12768, 12758, 12748, 12742, 12735, 12726, 12716, 12711, 12707, 12700, 12693, 12682, 12671, 12663, 12654, 12641, 12628, 12619, 12610, 12599, 12587, 12576, 12565, 12556, 12547, 12533, 12520, 12506, 12493, 12480, 12468, 12455, 12443, 12431, 12419, 12410, 12400, 12385, 12370, 12359, 12348, 12340, 12332, 12322, 12312, 12302, 12292, 12283, 12273, 12261, 12249, 12239, 12228, 12216, 12203, 12187, 12171, 12164, 12156, 12146, 12136, 12127, 12119, 12109, 12099, 12079, 12060, 12049, 12038, 12027, 12015, 12002, 11988, 11979, 11970, 11955, 11940, 11926, 11912, 11903, 11893, 11880, 11867, 11848, 11830, 11822, 11813, 11801, 11788, 11778, 11769, 11755, 11741, 11731, 11721, 11710, 11700, 11687, 11674, 11666, 11658, 11644, 11629, 11620, 11610, 11598, 11585, 11568, 11551, 11540, 11528, 11516, 11504, 11493, 11481, 11461, 11442, 11429, 11417, 11401, 11385, 11374, 11364, 11352, 11340, 11327, 11313, 11295, 11276, 11263, 11250, 11227, 11205, 11188, 11172, 11142, 11111, 11092, 11072, 11059, 11046, 11029, 11012, 10991, 10969, 10949, 10930, 10906, 10882, 10862, 10842, 10833, 10823, 10808, 10792, 10779, 10765, 10739, 10714, 10696, 10679, 10657, 10635, 10618, 10601, 10582, 10562, 10547, 10533, 10514, 10495, 10483, 10471, 10457, 10442, 10423, 10404, 10379, 10354, 10323, 10291, 10280, 10268, 10251, 10235, 10218, 10201, 10181, 10161, 10142, 10123, 10103, 10083, 10068, 10053, 10032, 10012, 9998, 9984, 9957, 9930, 9911, 9892, 9875, 9857, 9841, 9826, 9807, 9788, 9775, 9762, 9750, 9738, 9722, 9705, 9691, 9677, 9661, 9644, 9627, 9611, 9602, 9594, 9580, 9565, 9549, 9532, 9517, 9503, 9488, 9473, 9450, 9427, 9413, 9398, 9382, 9366, 9348, 9330, 9314, 9298, 9287, 9276, 9255, 9234, 9224, 9214, 9196, 9177, 9158, 9139, 9125, 9112, 9092, 9072, 9057, 9042, 9023, 9003, 8987, 8970, 8958, 8946, 8935, 8923, 8902, 8880, 8869, 8858, 8847, 8836, 8817, 8797, 8781, 8765, 8746, 8728, 8709, 8690, 8680, 8669, 8657, 8645, 8629, 8614, 8589, 8565, 8547, 8529, 8513, 8496, 8476, 8456, 8442, 8427, 8407, 8386, 8368, 8350, 8329, 8309, 8296, 8283, 8260, 8238, 8217, 8197, 8182, 8167, 8142, 8117, 8097, 8078, 8059, 8040, 8018, 7997, 7988, 7979, 7954, 7928, 7909, 7889, 7867, 7844, 7823, 7803, 7783, 7763, 7741, 7720, 7693, 7667, 7644, 7622, 7597, 7573, 7554, 7536, 7520, 7503, 7483, 7464, 7452, 7440, 7427, 7413, 7398, 7383, 7372, 7361, 7342, 7322, 7309, 7296, 7279, 7263, 7248, 7233, 7227, 7221, 7208, 7195, 7176, 7156, 7145, 7133, 7119, 7105, 7090, 7075, 7056, 7037, 7018, 6998, 6979, 6960, 6938, 6916, 6892, 6868, 6855, 6841, 6821, 6801, 6785, 6769, 6750, 6731, 6706, 6681, 6662, 6643, 6619, 6596, 6574, 6551, 6539, 6526, 6508, 6489, 6469, 6450, 6420, 6390, 6375, 6360, 6344, 6328, 6311, 6294, 6276, 6258, 6237, 6216, 6200, 6183, 6165, 6146, 6126, 6106, 6084, 6062, 6049, 6036, 6021, 6007, 5994, 5982, 5969, 5956, 5944, 5932, 5915, 5899, 5883, 5867, 5853, 5839, 5824, 5810, 5793, 5776, 5753, 5730, 5714, 5697, 5679, 5661, 5644, 5626, 5602, 5578, 5569, 5559, 5542, 5525, 5508, 5490, 5478, 5467, 5451, 5435, 5422, 5408, 5397, 5385, 5367, 5349, 5341, 5333, 5325, 5317, 5303, 5288, 5280};
    constexpr static std::array<uint16_t, 2048> bVec = {14302, 14298, 14294, 14286, 14279, 14274, 14269, 14262, 14255, 14246, 14237, 14233, 14230, 14223, 14216, 14212, 14208, 14199, 14190, 14184, 14178, 14172, 14167, 14160, 14153, 14147, 14141, 14132, 14123, 14117, 14110, 14104, 14098, 14094, 14089, 14081, 14072, 14064, 14057, 14048, 14040, 14032, 14024, 14017, 14009, 14004, 13999, 13992, 13986, 13976, 13966, 13957, 13948, 13941, 13934, 13926, 13918, 13909, 13900, 13891, 13882, 13872, 13862, 13854, 13845, 13839, 13833, 13825, 13816, 13807, 13799, 13791, 13783, 13769, 13755, 13749, 13743, 13738, 13732, 13724, 13716, 13706, 13696, 13688, 13680, 13667, 13654, 13637, 13619, 13607, 13594, 13586, 13577, 13566, 13555, 13545, 13535, 13519, 13503, 13494, 13485, 13460, 13435, 13428, 13421, 13409, 13398, 13388, 13377, 13368, 13360, 13348, 13337, 13325, 13313, 13306, 13298, 13284, 13271, 13260, 13250, 13236, 13222, 13214, 13207, 13195, 13183, 13172, 13161, 13153, 13144, 13132, 13120, 13112, 13104, 13095, 13085, 13080, 13074, 13063, 13052, 13048, 13044, 13036, 13029, 13019, 13010, 13001, 12992, 12976, 12959, 12948, 12936, 12927, 12918, 12909, 12900, 12893, 12887, 12878, 12870, 12864, 12858, 12848, 12839, 12830, 12822, 12811, 12801, 12794, 12788, 12777, 12767, 12758, 12749, 12742, 12734, 12722, 12709, 12698, 12686, 12674, 12661, 12652, 12644, 12637, 12631, 12620, 12610, 12601, 12592, 12577, 12561, 12551, 12542, 12532, 12521, 12507, 12494, 12485, 12476, 12467, 12459, 12443, 12428, 12419, 12410, 12399, 12388, 12374, 12360, 12347, 12334, 12327, 12319, 12311, 12302, 12287, 12271, 12254, 12238, 12224, 12210, 12193, 12176, 12164, 12152, 12139, 12127, 12111, 12095, 12085, 12076, 12062, 12048, 12038, 12028, 12015, 12001, 11993, 11985, 11974, 11964, 11942, 11920, 11906, 11893, 11875, 11856, 11841, 11825, 11808, 11790, 11778, 11765, 11752, 11738, 11729, 11720, 11710, 11700, 11691, 11681, 11671, 11661, 11641, 11621, 11606, 11591, 11576, 11562, 11546, 11530, 11515, 11499, 11488, 11476, 11464, 11451, 11443, 11435, 11421, 11407, 11392, 11376, 11362, 11348, 11331, 11313, 11303, 11294, 11277, 11260, 11249, 11238, 11224, 11210, 11191, 11171, 11158, 11145, 11127, 11109, 11097, 11085, 11067, 11049, 11037, 11025, 11016, 11007, 10993, 10978, 10963, 10948, 10936, 10924, 10909, 10893, 10885, 10877, 10865, 10854, 10839, 10825, 10811, 10797, 10779, 10761, 10747, 10732, 10714, 10695, 10683, 10671, 10659, 10646, 10631, 10616, 10602, 10587, 10570, 10553, 10541, 10529, 10517, 10504, 10487, 10469, 10460, 10450, 10432, 10414, 10392, 10370, 10357, 10344, 10328, 10312, 10299, 10287, 10272, 10256, 10243, 10230, 10216, 10203, 10193, 10183, 10171, 10159, 10141, 10123, 10108, 10092, 10079, 10065, 10056, 10046, 10037, 10027, 10014, 10001, 9990, 9980, 9970, 9960, 9953, 9947, 9937, 9927, 9916, 9905, 9898, 9892, 9882, 9872, 9859, 9846, 9837, 9828, 9823, 9818, 9810, 9803, 9795, 9786, 9780, 9774, 9763, 9752, 9744, 9736, 9726, 9717, 9709, 9702, 9695, 9688, 9679, 9670, 9661, 9651, 9642, 9633, 9622, 9611, 9602, 9593, 9585, 9577, 9569, 9560, 9550, 9539, 9533, 9528, 9522, 9515, 9506, 9498, 9489, 9480, 9472, 9465, 9457, 9449, 9442, 9434, 9422, 9410, 9401, 9392, 9388, 9383, 9374, 9366, 9361, 9356, 9345, 9334, 9326, 9319, 9309, 9298, 9289, 9281, 9275, 9269, 9260, 9251, 9243, 9234, 9219, 9204, 9198, 9191, 9185, 9178, 9170, 9163, 9155, 9148, 9140, 9132, 9126, 9120, 9112, 9104, 9098, 9092, 9082, 9073, 9067, 9062, 9055, 9049, 9039, 9030, 9022, 9014, 9008, 9002, 8996, 8990, 8985, 8979, 8975, 8971, 8965, 8960, 8955, 8951, 8948, 8945, 8937, 8929, 8925, 8920, 8915, 8910, 8906, 8901, 8896, 8891, 8887, 8882, 8877, 8872, 8869, 8866, 8862, 8857, 8851, 8845, 8841, 8838, 8835, 8833, 8828, 8823, 8820, 8816, 8810, 8804, 8801, 8798, 8793, 8789, 8783, 8778, 8775, 8772, 8769, 8766, 8761, 8756, 8753, 8750, 8749, 8747, 8743, 8740, 8739, 8737, 8733, 8729, 8728, 8726, 8722, 8718, 8716, 8713, 8708, 8703, 8699, 8695, 8692, 8689, 8685, 8681, 8678, 8675, 8670, 8666, 8665, 8664, 8660, 8657, 8653, 8650, 8647, 8644, 8641, 8638, 8636, 8633, 8630, 8626, 8623, 8620, 8615, 8610, 8606, 8602, 8598, 8594, 8591, 8589, 8585, 8581, 8579, 8577, 8573, 8570, 8567, 8565, 8561, 8558, 8553, 8549, 8547, 8544, 8540, 8536, 8533, 8531, 8527, 8522, 8520, 8519, 8517, 8516, 8514, 8513, 8513, 8512, 8509, 8506, 8505, 8504, 8503, 8501, 8499, 8497, 8498, 8499, 8497, 8495, 8494, 8494, 8493, 8492, 8491, 8490, 8491, 8491, 8492, 8493, 8493, 8493, 8492, 8491, 8491, 8492, 8492, 8492, 8492, 8491, 8491, 8491, 8492, 8493, 8492, 8492, 8491, 8491, 8490, 8489, 8492, 8494, 8492, 8490, 8491, 8493, 8494, 8495, 8496, 8498, 8499, 8501, 8501, 8501, 8501, 8501, 8502, 8503, 8503, 8503, 8505, 8506, 8509, 8513, 8512, 8512, 8513, 8515, 8517, 8518, 8519, 8520, 8522, 8523, 8525, 8527, 8528, 8530, 8532, 8534, 8534, 8535, 8536, 8538, 8539, 8540, 8541, 8541, 8544, 8547, 8547, 8546, 8549, 8551, 8552, 8553, 8555, 8557, 8560, 8562, 8564, 8566, 8568, 8570, 8570, 8571, 8575, 8579, 8580, 8581, 8582, 8583, 8584, 8586, 8589, 8591, 8592, 8593, 8596, 8599, 8600, 8601, 8604, 8606, 8611, 8617, 8618, 8619, 8622, 8625, 8627, 8630, 8633, 8637, 8639, 8640, 8645, 8649, 8651, 8653, 8656, 8659, 8661, 8664, 8666, 8668, 8671, 8673, 8677, 8680, 8682, 8684, 8688, 8691, 8692, 8693, 8697, 8700, 8704, 8709, 8711, 8713, 8717, 8722, 8727, 8731, 8733, 8734, 8738, 8743, 8747, 8752, 8757, 8762, 8767, 8772, 8776, 8779, 8782, 8784, 8788, 8791, 8797, 8804, 8807, 8811, 8815, 8819, 8825, 8831, 8835, 8838, 8843, 8848, 8850, 8853, 8857, 8860, 8865, 8870, 8873, 8875, 8878, 8882, 8887, 8893, 8895, 8898, 8901, 8904, 8911, 8918, 8923, 8927, 8932, 8937, 8940, 8943, 8947, 8950, 8954, 8958, 8961, 8965, 8971, 8977, 8982, 8987, 8994, 9000, 9007, 9013, 9017, 9021, 9029, 9036, 9041, 9046, 9051, 9057, 9064, 9071, 9078, 9084, 9089, 9094, 9103, 9112, 9116, 9121, 9127, 9133, 9140, 9146, 9153, 9160, 9171, 9182, 9190, 9197, 9201, 9205, 9213, 9220, 9228, 9235, 9243, 9250, 9258, 9266, 9272, 9278, 9285, 9292, 9301, 9310, 9318, 9326, 9336, 9346, 9355, 9364, 9372, 9381, 9391, 9401, 9416, 9431, 9442, 9454, 9466, 9478, 9486, 9494, 9504, 9514, 9526, 9538, 9547, 9557, 9566, 9575, 9583, 9592, 9601, 9610, 9619, 9628, 9640, 9651, 9657, 9663, 9674, 9686, 9698, 9711, 9720, 9729, 9736, 9744, 9754, 9765, 9778, 9791, 9802, 9813, 9827, 9842, 9851, 9860, 9872, 9883, 9893, 9902, 9916, 9930, 9942, 9954, 9965, 9976, 9986, 9996, 10011, 10026, 10037, 10047, 10060, 10072, 10083, 10094, 10105, 10116, 10124, 10132, 10156, 10180, 10190, 10199, 10213, 10226, 10241, 10255, 10267, 10280, 10289, 10299, 10310, 10321, 10337, 10352, 10366, 10380, 10396, 10411, 10424, 10436, 10446, 10457, 10465, 10474, 10486, 10497, 10512, 10526, 10543, 10561, 10573, 10586, 10598, 10610, 10620, 10631, 10643, 10656, 10667, 10678, 10691, 10705, 10716, 10728, 10741, 10755, 10774, 10793, 10800, 10808, 10823, 10837, 10854, 10871, 10881, 10892, 10906, 10920, 10930, 10941, 10951, 10961, 10973, 10985, 10994, 11003, 11021, 11039, 11051, 11063, 11078, 11094, 11104, 11114, 11127, 11139, 11148, 11157, 11168, 11178, 11191, 11204, 11219, 11234, 11253, 11272, 11282, 11293, 11300, 11307, 11323, 11339, 11352, 11365, 11371, 11377, 11388, 11399, 11412, 11424, 11438, 11451, 11465, 11479, 11496, 11514, 11522, 11531, 11542, 11553, 11568, 11583, 11595, 11606, 11623, 11640, 11654, 11667, 11677, 11686, 11699, 11711, 11724, 11737, 11752, 11768, 11779, 11791, 11815, 11839, 11846, 11853, 11864, 11875, 11891, 11907, 11917, 11928, 11940, 11953, 11971, 11989, 12003, 12017, 12028, 12040, 12050, 12061, 12072, 12083, 12095, 12107, 12121, 12134, 12144, 12154, 12164, 12174, 12188, 12203, 12219, 12235, 12249, 12263, 12275, 12287, 12300, 12313, 12327, 12341, 12355, 12369, 12379, 12389, 12404, 12420, 12432, 12444, 12452, 12459, 12470, 12481, 12493, 12505, 12517, 12530, 12540, 12551, 12564, 12576, 12585, 12594, 12604, 12615, 12628, 12641, 12649, 12657, 12669, 12681, 12695, 12708, 12722, 12735, 12746, 12757, 12769, 12780, 12791, 12802, 12822, 12842, 12851, 12860, 12873, 12886, 12900, 12914, 12924, 12934, 12945, 12955, 12966, 12977, 12984, 12991, 13001, 13012, 13022, 13033, 13045, 13057, 13067, 13078, 13088, 13097, 13105, 13113, 13124, 13135, 13147, 13160, 13169, 13179, 13187, 13194, 13202, 13211, 13221, 13232, 13240, 13249, 13257, 13266, 13274, 13281, 13289, 13297, 13306, 13316, 13323, 13331, 13337, 13343, 13358, 13373, 13381, 13389, 13395, 13401, 13408, 13415, 13422, 13428, 13434, 13440, 13449, 13458, 13466, 13473, 13481, 13488, 13493, 13497, 13505, 13513, 13524, 13535, 13543, 13551, 13558, 13564, 13575, 13585, 13594, 13603, 13612, 13620, 13628, 13637, 13644, 13652, 13659, 13667, 13674, 13682, 13688, 13695, 13702, 13710, 13716, 13722, 13725, 13729, 13737, 13744, 13754, 13763, 13772, 13781, 13787, 13794, 13805, 13816, 13824, 13832, 13837, 13841, 13849, 13856, 13870, 13884, 13892, 13901, 13909, 13918, 13924, 13931, 13936, 13942, 13948, 13954, 13961, 13969, 13972, 13976, 13982, 13989, 13996, 14003, 14009, 14015, 14024, 14034, 14042, 14050, 14058, 14067, 14074, 14082, 14088, 14095, 14104, 14113, 14119, 14125, 14131, 14138, 14143, 14148, 14155, 14161, 14167, 14173, 14181, 14188, 14194, 14199, 14206, 14213, 14219, 14224, 14230, 14235, 14242, 14248, 14254, 14259, 14265, 14270, 14274, 14278, 14281, 14284, 14287, 14289, 14292, 14295, 14299, 14302, 14308, 14313, 14317, 14320, 14325, 14330, 14336, 14341, 14347, 14353, 14360, 14367, 14375, 14384, 14388, 14392, 14401, 14410, 14420, 14429, 14439, 14449, 14455, 14460, 14464, 14468, 14473, 14477, 14483, 14489, 14494, 14499, 14505, 14511, 14516, 14522, 14532, 14542, 14545, 14548, 14555, 14562, 14567, 14572, 14577, 14582, 14593, 14603, 14609, 14614, 14620, 14625, 14630, 14634, 14640, 14646, 14651, 14655, 14661, 14668, 14673, 14677, 14685, 14692, 14699, 14706, 14710, 14714, 14721, 14728, 14735, 14742, 14747, 14753, 14758, 14763, 14771, 14779, 14783, 14787, 14791, 14794, 14799, 14803, 14809, 14816, 14823, 14829, 14837, 14844, 14849, 14854, 14859, 14865, 14869, 14874, 14878, 14883, 14886, 14889, 14892, 14896, 14899, 14901, 14906, 14911, 14914, 14917, 14920, 14922, 14926, 14930, 14933, 14937, 14940, 14942, 14945, 14947, 14950, 14954, 14958, 14962, 14965, 14967, 14971, 14975, 14978, 14982, 14986, 14991, 14993, 14995, 14999, 15004, 15008, 15011, 15015, 15018, 15020, 15022, 15025, 15028, 15030, 15032, 15034, 15036, 15039, 15041, 15042, 15044, 15046, 15049, 15053, 15056, 15058, 15060, 15064, 15067, 15068, 15069, 15072, 15075, 15077, 15079, 15081, 15082, 15085, 15087, 15088, 15089, 15091, 15093, 15095, 15096, 15097, 15097, 15099, 15100, 15102, 15104, 15105, 15105, 15106, 15108, 15108, 15109, 15110, 15111, 15111, 15111, 15113, 15115, 15115, 15116, 15117, 15118, 15118, 15118, 15120, 15121, 15122, 15122, 15122, 15122, 15123, 15123, 15123, 15124, 15124, 15124, 15124, 15125, 15127, 15128, 15130, 15131, 15130, 15129, 15129, 15130, 15131, 15132, 15132, 15133, 15133, 15134, 15134, 15135, 15136, 15137, 15137, 15138, 15139, 15141, 15140, 15139, 15141, 15143, 15143, 15144, 15145, 15146, 15148, 15150, 15152, 15153, 15154, 15154, 15156, 15157, 15158, 15159, 15160, 15161, 15163, 15165, 15167, 15169, 15171, 15172, 15176, 15179, 15180, 15181, 15182, 15182, 15184, 15185, 15187, 15188, 15188, 15189, 15190, 15191, 15192, 15194, 15194, 15194, 15196, 15198, 15199, 15200, 15201, 15202, 15203, 15204, 15205, 15206, 15207, 15209, 15209, 15209, 15210, 15211, 15212, 15213, 15215, 15216, 15218, 15219, 15220, 15221, 15222, 15223, 15222, 15221, 15222, 15222, 15222, 15221, 15219, 15217, 15218, 15218, 15218, 15218, 15218, 15218, 15220, 15222, 15222, 15222, 15223, 15225, 15225, 15224, 15224, 15223, 15223, 15224, 15224, 15225, 15224, 15224, 15225, 15225, 15225, 15225, 15225, 15224, 15224, 15223, 15222, 15221, 15220, 15219, 15219, 15219, 15218, 15218, 15218, 15217, 15217, 15217, 15217, 15217, 15216, 15216, 15215, 15214, 15214, 15213, 15213, 15213, 15211, 15210, 15208, 15205, 15203, 15201, 15199, 15197, 15195, 15193, 15192, 15192, 15190, 15189, 15188, 15188, 15188, 15188, 15187, 15186, 15187, 15187, 15186, 15184, 15184, 15184, 15184, 15183, 15180, 15178, 15177, 15176, 15175, 15173, 15171, 15170, 15169, 15168, 15166, 15164, 15163, 15162, 15160, 15158, 15158, 15158, 15156, 15153, 15153, 15152, 15149, 15146, 15146, 15145, 15145, 15145, 15143, 15141, 15140, 15138, 15136, 15134, 15131, 15128, 15126, 15123, 15121, 15120, 15119, 15118, 15118, 15117, 15116, 15115, 15114, 15112, 15112, 15111, 15110, 15109, 15108, 15107, 15107, 15107, 15105, 15102, 15101, 15099, 15096, 15093, 15091, 15089, 15087, 15085, 15084, 15082, 15080, 15077, 15074, 15071, 15066, 15062, 15060, 15059, 15055, 15051, 15047, 15044, 15042, 15041, 15038, 15036, 15033, 15031, 15029, 15028, 15025, 15022, 15020, 15019, 15017, 15015, 15012, 15010, 15007, 15003, 15000, 14996, 14993, 14989, 14989, 14989, 14987, 14985, 14983, 14981, 14979, 14977, 14976, 14975, 14973, 14972, 14969, 14967, 14963, 14959, 14956, 14952, 14948, 14945, 14941, 14937, 14932, 14928, 14924, 14920, 14917, 14914, 14912, 14909, 14906, 14903, 14900, 14896, 14893, 14890, 14888, 14887, 14884, 14882, 14878, 14874, 14874, 14874, 14871, 14868, 14862, 14857, 14855, 14853, 14851, 14848, 14845, 14843, 14838, 14833, 14830, 14826, 14822, 14818, 14813, 14809, 14804, 14800, 14796, 14793, 14789, 14786, 14782, 14779, 14774, 14769, 14764, 14759, 14755, 14751, 14746, 14740, 14735, 14730, 14727, 14723, 14718, 14712, 14708, 14704, 14698, 14691, 14687, 14682, 14676, 14671, 14665, 14659, 14655, 14652, 14647, 14642, 14637, 14633, 14629, 14624, 14618, 14611, 14605, 14599, 14594, 14589, 14584, 14580, 14576, 14572, 14567, 14562, 14557, 14552, 14546, 14541, 14536, 14532, 14524, 14517, 14513, 14510, 14505, 14500, 14492, 14485, 14480, 14476, 14470, 14465, 14459, 14454, 14446, 14439, 14435, 14431, 14423, 14414, 14409, 14404, 14398, 14392, 14385, 14379, 14374, 14370, 14364, 14359, 14351, 14343, 14341, 14339, 14334, 14329, 14321, 14314, 14308};

    constexpr static float pwmToStallCurrent{1.0f};

    constexpr static float backEmfCurrent{-0.0001397607579124993f};

    constexpr static float friction{60.0f};

    constexpr static uint16_t pwmOffset{500};

    SimulationHandler();

    float getPosition();

    void setPwm(int16_t pwm);

private:
    void update();

    bool newCycle{false};
    int16_t pwm{0};
    Eigen::Vector3f xSim;
    Eigen::Matrix3f aSim;
    Eigen::Vector3f bSim;
    float uSimFricInvC;
};

class OpticalEncoderSim : public OpticalEncoderHandler
{
public:
    OpticalEncoderSim(SimulationHandler& simHandler,
                const std::array<uint16_t, vecSize>& aVec, const std::array<uint16_t, vecSize>& bVec,
                int16_t sensor1Pin, int16_t sensor2Pin, float unitsPerRev);

    virtual void init() override;

    virtual void triggerSample() override;

    virtual float getValue() override;

    static int32_t calcWrapAroundIndex(int32_t i);

    SimulationHandler& simHandler;
    const float gearingInv;
};

class ResistiveEncoderSim : public ResistiveEncoderHandler
{
public:
    ResistiveEncoderSim(SimulationHandler& simHandler, int16_t pin, float unitsPerRev,
            const std::array<int16_t, vecSize>& compVec = {0});

    virtual void init() override;

    virtual void triggerSample() override;

    virtual float getValue() override;

    SimulationHandler& simHandler;
    float scalingInv;
};

class PwmHandlerSim : public PwmHandler
{
public:
    typedef uint16_t (*LinearizeFunctionType)(uint16_t);

    PwmHandlerSim(SimulationHandler& simHandler, 
            LinearizeFunctionType linearizeFunction = [](uint16_t in){return in;});

    virtual int setOutput(int output) override;

    virtual void activateBrake() override;

    virtual void disconnectOutput() override {}

    virtual void connectOutput() override {}

    SimulationHandler& simHandler;
    const LinearizeFunctionType linearizeFunction;
};

#endif
