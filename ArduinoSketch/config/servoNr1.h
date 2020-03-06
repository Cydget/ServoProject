#include <Eigen.h>
#include "../EncoderHandler.h"
#include "../OpticalEncoderHandler.h"
#include "../ArduinoC++BugFixes.h"

#ifndef CONFIG_HOLDER_H
#define CONFIG_HOLDER_H

class ConfigHolder
{
public:
    static constexpr float getMainEncoderGearRation()
    {
        return 275.0 / 125904.0;
    }

    static std::unique_ptr<OpticalEncoderHandler> createMainEncoderHandler()
    {
        std::array<uint16_t, 512> aVec = {3040, 3031, 3022, 3013, 3007, 3001, 2997, 2984, 2972, 2959, 2946, 2940, 2927, 2920, 2915, 2907, 2885, 2874, 2869, 2857, 2843, 2833, 2826, 2803, 2789, 2778, 2768, 2758, 2748, 2740, 2730, 2713, 2700, 2684, 2673, 2662, 2656, 2650, 2642, 2628, 2613, 2606, 2598, 2589, 2580, 2574, 2565, 2554, 2547, 2538, 2535, 2527, 2516, 2508, 2498, 2494, 2494, 2490, 2485, 2478, 2468, 2464, 2459, 2460, 2457, 2453, 2448, 2446, 2442, 2444, 2439, 2440, 2438, 2434, 2429, 2426, 2424, 2422, 2418, 2418, 2409, 2410, 2404, 2399, 2394, 2392, 2389, 2386, 2382, 2373, 2368, 2363, 2357, 2353, 2351, 2348, 2344, 2339, 2338, 2339, 2341, 2339, 2339, 2338, 2336, 2338, 2339, 2339, 2344, 2346, 2344, 2344, 2345, 2344, 2345, 2348, 2352, 2352, 2352, 2352, 2351, 2354, 2350, 2351, 2354, 2353, 2358, 2359, 2356, 2359, 2360, 2362, 2361, 2357, 2358, 2356, 2353, 2350, 2351, 2346, 2343, 2340, 2339, 2338, 2336, 2334, 2337, 2336, 2336, 2338, 2340, 2343, 2347, 2348, 2353, 2351, 2354, 2356, 2364, 2368, 2377, 2378, 2380, 2382, 2381, 2388, 2392, 2397, 2402, 2406, 2407, 2410, 2416, 2424, 2433, 2437, 2444, 2449, 2457, 2465, 2477, 2485, 2497, 2509, 2519, 2530, 2535, 2543, 2554, 2570, 2578, 2586, 2596, 2606, 2611, 2639, 2638, 2649, 2665, 2683, 2684, 2692, 2701, 2717, 2728, 2742, 2754, 2761, 2769, 2775, 2781, 2789, 2805, 2816, 2828, 2836, 2841, 2849, 2859, 2876, 2886, 2892, 2902, 2904, 2922, 2936, 2941, 2954, 2960, 2969, 2979, 2995, 3007, 3016, 3024, 3033, 3039, 3050, 3064, 3079, 3094, 3110, 3114, 3117, 3123, 3130, 3144, 3157, 3169, 3172, 3182, 3192, 3198, 3206, 3210, 3214, 3222, 3227, 3232, 3236, 3241, 3247, 3254, 3258, 3264, 3270, 3280, 3290, 3292, 3295, 3300, 3301, 3308, 3322, 3324, 3330, 3338, 3345, 3348, 3354, 3356, 3371, 3382, 3390, 3396, 3401, 3407, 3413, 3429, 3430, 3433, 3438, 3442, 3452, 3461, 3465, 3472, 3486, 3498, 3502, 3507, 3513, 3524, 3525, 3533, 3537, 3538, 3540, 3538, 3539, 3544, 3547, 3554, 3558, 3562, 3571, 3579, 3578, 3589, 3592, 3604, 3614, 3611, 3617, 3623, 3625, 3629, 3637, 3644, 3646, 3644, 3645, 3648, 3646, 3646, 3646, 3648, 3644, 3646, 3649, 3654, 3656, 3655, 3655, 3657, 3659, 3662, 3665, 3674, 3680, 3682, 3683, 3681, 3678, 3678, 3674, 3676, 3674, 3678, 3681, 3687, 3687, 3688, 3686, 3686, 3689, 3696, 3701, 3704, 3705, 3706, 3708, 3707, 3703, 3700, 3698, 3696, 3700, 3702, 3702, 3698, 3700, 3698, 3696, 3695, 3696, 3692, 3686, 3685, 3685, 3688, 3689, 3689, 3692, 3693, 3693, 3694, 3694, 3696, 3698, 3700, 3702, 3701, 3702, 3704, 3706, 3707, 3711, 3710, 3709, 3710, 3712, 3711, 3708, 3704, 3702, 3699, 3694, 3692, 3690, 3688, 3684, 3680, 3676, 3670, 3666, 3659, 3651, 3647, 3645, 3641, 3637, 3624, 3623, 3615, 3610, 3599, 3594, 3587, 3581, 3571, 3562, 3555, 3551, 3543, 3535, 3515, 3494, 3488, 3484, 3480, 3477, 3473, 3468, 3460, 3457, 3454, 3444, 3438, 3433, 3426, 3413, 3408, 3404, 3399, 3394, 3391, 3389, 3384, 3378, 3373, 3364, 3362, 3355, 3350, 3344, 3340, 3330, 3326, 3321, 3314, 3312, 3305, 3294, 3286, 3284, 3276, 3272, 3265, 3254, 3245, 3238, 3224, 3214, 3206, 3196, 3191, 3184, 3176, 3157, 3145, 3140, 3138, 3135, 3130, 3117, 3094, 3090, 3077, 3066, 3065, 3058};
        std::array<uint16_t, 512> bVec = {2941, 2941, 2939, 2938, 2938, 2938, 2936, 2933, 2931, 2930, 2927, 2927, 2921, 2916, 2918, 2917, 2915, 2916, 2916, 2915, 2917, 2918, 2917, 2920, 2921, 2922, 2926, 2926, 2927, 2928, 2932, 2934, 2942, 2941, 2945, 2949, 2950, 2950, 2952, 2955, 2966, 2962, 2967, 2968, 2971, 2972, 2980, 2988, 2994, 2998, 3002, 3006, 3017, 3026, 3036, 3042, 3046, 3051, 3061, 3070, 3077, 3081, 3090, 3093, 3097, 3107, 3116, 3131, 3132, 3135, 3144, 3150, 3158, 3168, 3176, 3183, 3190, 3199, 3204, 3212, 3218, 3223, 3231, 3236, 3241, 3249, 3256, 3263, 3276, 3282, 3286, 3291, 3298, 3308, 3318, 3321, 3327, 3338, 3340, 3348, 3355, 3364, 3377, 3384, 3388, 3392, 3393, 3396, 3408, 3422, 3427, 3430, 3434, 3441, 3445, 3452, 3459, 3464, 3467, 3473, 3481, 3486, 3487, 3491, 3503, 3504, 3506, 3517, 3513, 3515, 3518, 3524, 3526, 3528, 3530, 3534, 3542, 3547, 3550, 3556, 3558, 3560, 3562, 3566, 3572, 3580, 3584, 3586, 3589, 3596, 3600, 3610, 3615, 3621, 3622, 3625, 3629, 3631, 3640, 3645, 3650, 3654, 3656, 3657, 3662, 3668, 3675, 3680, 3688, 3695, 3692, 3696, 3702, 3711, 3713, 3715, 3716, 3717, 3716, 3717, 3718, 3719, 3724, 3727, 3732, 3737, 3741, 3746, 3749, 3758, 3762, 3766, 3769, 3771, 3774, 3780, 3782, 3783, 3784, 3782, 3785, 3784, 3784, 3784, 3786, 3783, 3784, 3788, 3787, 3789, 3789, 3790, 3788, 3788, 3793, 3794, 3798, 3801, 3806, 3808, 3807, 3808, 3804, 3801, 3802, 3801, 3804, 3806, 3810, 3811, 3811, 3809, 3809, 3809, 3812, 3814, 3817, 3820, 3824, 3827, 3825, 3820, 3820, 3819, 3818, 3817, 3821, 3822, 3819, 3820, 3816, 3818, 3818, 3816, 3813, 3812, 3811, 3811, 3812, 3815, 3817, 3817, 3819, 3819, 3820, 3820, 3821, 3825, 3824, 3827, 3828, 3827, 3828, 3829, 3831, 3833, 3835, 3833, 3835, 3833, 3835, 3836, 3833, 3832, 3829, 3828, 3828, 3825, 3818, 3821, 3819, 3819, 3812, 3811, 3807, 3805, 3804, 3798, 3795, 3794, 3792, 3790, 3785, 3783, 3782, 3774, 3770, 3769, 3764, 3763, 3758, 3751, 3746, 3745, 3740, 3733, 3726, 3721, 3713, 3707, 3697, 3692, 3689, 3690, 3690, 3687, 3684, 3680, 3676, 3673, 3674, 3669, 3668, 3662, 3654, 3648, 3646, 3643, 3642, 3639, 3637, 3635, 3630, 3628, 3622, 3623, 3620, 3616, 3610, 3607, 3602, 3600, 3598, 3594, 3591, 3586, 3581, 3576, 3574, 3570, 3562, 3560, 3556, 3547, 3537, 3530, 3525, 3519, 3516, 3510, 3505, 3495, 3489, 3485, 3478, 3473, 3470, 3468, 3464, 3454, 3442, 3438, 3431, 3424, 3420, 3416, 3406, 3398, 3394, 3388, 3382, 3378, 3368, 3360, 3355, 3350, 3346, 3336, 3329, 3316, 3306, 3298, 3292, 3287, 3276, 3268, 3258, 3248, 3245, 3238, 3232, 3225, 3215, 3207, 3194, 3185, 3173, 3166, 3161, 3156, 3151, 3145, 3136, 3132, 3126, 3118, 3104, 3097, 3092, 3087, 3084, 3080, 3071, 3062, 3057, 3053, 3048, 3048, 3046, 3043, 3039, 3032, 3028, 3027, 3025, 3026, 3021, 3016, 3016, 3015, 3013, 3011, 3011, 3008, 3006, 3004, 3002, 3002, 3001, 2999, 2996, 2990, 2983, 2982, 2979, 2976, 2976, 2972, 2970, 2970, 2966, 2961, 2957, 2954, 2945, 2945, 2944, 2940, 2938, 2935, 2935, 2932, 2932, 2931, 2929, 2932, 2931, 2933, 2931, 2932, 2935, 2935, 2936, 2937, 2936, 2937, 2934, 2938, 2936, 2940, 2939, 2936, 2941, 2938, 2939, 2937, 2937, 2938, 2942, 2942, 2940, 2940};

        return std::make_unique<OpticalEncoderHandler>(aVec, bVec);
    }

    static std::unique_ptr<EncoderHandlerInterface> createOutputEncoderHandler()
    {
        return std::make_unique<EncoderHandler>(A5);
    }

    static constexpr unsigned char getCommunicationId()
    {
        return 1;
    }

    static Eigen::Matrix<float, 5, 1> getControlParameterVector()
    {
        Eigen::Matrix<float, 5, 1> L;
        //L << 9.940239281724569, 1.3586010780478561, -0.03237764040441623, -0.03237764040441623 * 10, 12;
        //L << 14.865806368082696, 2.0623236695442064, -0.07122297702645312, -0.07122297702645312 * 10, 12;
        //L << 19.76190853507559, 2.7501424347363677, -0.12380201903044662, -0.12380201903044662 * 10, 12;
        L << 24.628722042909875, 3.422417759025543, -0.18915403084733035, -0.18915403084733035 * 10, 12;
        //L << 57.89092015732856, 7.721727677879117, -0.9336154818877859, -0.9336154818877859 * 10, 12;
        //L << 94.23296940236878, 11.862863259936727, -2.185085156962166, -2.185085156962166 * 10, 12;

        return L;
    }

    class KalmanFilter
    {
      public:
        static Eigen::Vector3f getKVector()
        {
            Eigen::Vector3f K;
            
            //K << 0.09799424580193117,
            //    2.4964409292865963,
            //    0.5652699951929046;

            //K << 0.16531265413057228,
            //    7.247273820257207,
            //    2.5269719748600346;

            //K << 0.1983825910518331,
            //    10.478680647096779,
            //    4.291072093854287;

            //K << 0.32684007265646386,
            //    28.567812385253276,
            //    18.53313095588553;

            //K << 0.3888374995706161,
            //    40.40850366768767,
            //    30.93862171115473;

            //K << 0.4791413260700308,
            //    61.21885215942826,
            //    57.39263621353391;

            //K << 0.5085413648625792,
            //    68.89605951297686,
            //    68.47216577817979;

            //K << 0.622743534980963,
            //    102.86198025189901,
            //    124.93406815357332;

            // 30 * 4 * 2 pole
            //K << 0.7316969391112194,
            //    141.316769493361,
            //    201.79065187534968;

            // 60 * 4 * 2 pole
            K << 1.2879572201280896,
                425.2887752180842,
                1089.0860221513021;

            // 100 * 4 * 2 pole
            //K << 1.8229097365190623,
            //    825.8706566376411,
            //    3075.4863531454275;

            return K;
        }


        static Eigen::Matrix3f getAMatrix()
        {
            Eigen::Matrix3f A;
            A << 1.0, 0.0012, 3.6719999999999994e-05,
            0.0, 0.994, 0.0612,
            0.0, 0.0, 1.0;

            return A;
        }

        static Eigen::Matrix3f getAInvMatrix()
        {
            Eigen::Matrix3f AInv;

            AInv << 1.0, -0.0012072434607645873, 3.7163299798792755e-05,
                0.0, 1.0060362173038229, -0.06156941649899396,
                0.0, 0.0, 1.0;

            return AInv;
        }

        static Eigen::Vector3f getBVector()
        {
            Eigen::Vector3f B;

            B << 3.6719999999999994e-05,
                0.0612,
                0.0;

            return B;
        }
    };
};

#endif
