#include "OpticalEncoderHandler.h"

uint16_t debugValue = 0;

uint16_t OpticalEncoderHandler::getDebugValue()
{
    return debugValue;
}

OpticalEncoderHandler::OpticalEncoderHandler(const std::array<uint16_t, 512>& aVec, const std::array<uint16_t, 512>& bVec) :
    aVec(aVec), bVec(bVec), sensor1(A2), sensor2(A3), value(0), wrapAroundCorretion(0), newData(false)
{
}

OpticalEncoderHandler::~OpticalEncoderHandler()
{
}

void OpticalEncoderHandler::init()
{
    AdcHandler::init();

    triggerSample();
    getValue();
}

void OpticalEncoderHandler::triggerSample()
{
    sensor1.triggerSample();
    sensor2.triggerSample();

    newData = true;
}

float OpticalEncoderHandler::getValue()
{
    if (newData)
    {
        newData = false;
        updatePosition();
    }

    return (value + wrapAroundCorretion);
}

//uint16_t aVec[] = {3395, 3383, 3367, 3357, 3353, 3350, 3350, 3357, 3358, 3345, 3340, 3332, 3326, 3315, 3311, 3303, 3295, 3287, 3284, 3279, 3278, 3270, 3257, 3246, 3239, 3233, 3228, 3224, 3218, 3206, 3193, 3185, 3173, 3166, 3155, 3152, 3143, 3129, 3124, 3111, 3097, 3088, 3075, 3060, 3048, 3035, 3029, 3016, 3007, 2990, 2965, 2941, 2927, 2920, 2908, 2899, 2882, 2863, 2846, 2833, 2819, 2802, 2784, 2764, 2743, 2721, 2698, 2682, 2664, 2646, 2628, 2611, 2593, 2577, 2564, 2553, 2534, 2523, 2500, 2472, 2453, 2438, 2425, 2411, 2383, 2359, 2328, 2312, 2288, 2260, 2232, 2202, 2174, 2145, 2113, 2089, 2075, 2046, 2018, 2000, 1984, 1964, 1953, 1940, 1921, 1907, 1892, 1872, 1857, 1845, 1838, 1828, 1816, 1806, 1790, 1780, 1767, 1754, 1739, 1725, 1708, 1687, 1663, 1638, 1627, 1608, 1584, 1571, 1560, 1546, 1538, 1528, 1518, 1509, 1500, 1491, 1484, 1475, 1468, 1455, 1446, 1434, 1422, 1413, 1398, 1383, 1364, 1350, 1327, 1302, 1275, 1258, 1240, 1215, 1199, 1186, 1172, 1168, 1160, 1145, 1137, 1129, 1120, 1117, 1107, 1102, 1095, 1084, 1079, 1077, 1070, 1066, 1060, 1057, 1049, 1046, 1036, 1027, 1021, 1016, 1010, 1005, 999, 994, 991, 988, 985, 980, 974, 966, 964, 963, 956, 955, 943, 936, 932, 929, 924, 918, 916, 916, 914, 915, 914, 919, 924, 930, 936, 942, 946, 954, 954, 960, 969, 975, 980, 985, 988, 995, 1001, 1011, 1017, 1028, 1035, 1040, 1047, 1058, 1068, 1071, 1089, 1106, 1123, 1138, 1151, 1163, 1178, 1185, 1198, 1211, 1221, 1231, 1246, 1256, 1261, 1269, 1280, 1287, 1298, 1307, 1317, 1327, 1336, 1345, 1354, 1366, 1375, 1382, 1401, 1419, 1441, 1463, 1480, 1497, 1512, 1528, 1548, 1561, 1574, 1596, 1611, 1628, 1636, 1647, 1662, 1676, 1696, 1711, 1733, 1751, 1773, 1786, 1804, 1819, 1835, 1853, 1875, 1903, 1922, 1938, 1950, 1965, 1979, 1996, 2016, 2032, 2043, 2062, 2072, 2080, 2096, 2102, 2112, 2128, 2141, 2156, 2176, 2201, 2224, 2242, 2261, 2281, 2298, 2326, 2347, 2386, 2422, 2443, 2462, 2478, 2496, 2512, 2538, 2554, 2574, 2593, 2602, 2612, 2625, 2639, 2648, 2667, 2684, 2703, 2729, 2751, 2775, 2804, 2822, 2839, 2858, 2877, 2887, 2908, 2932, 2951, 2964, 2977, 2989, 3003, 3014, 3023, 3035, 3045, 3054, 3060, 3068, 3076, 3085, 3095, 3106, 3118, 3131, 3142, 3156, 3162, 3172, 3189, 3197, 3203, 3216, 3231, 3242, 3249, 3246, 3254, 3261, 3267, 3272, 3282, 3287, 3290, 3295, 3298, 3304, 3309, 3315, 3321, 3334, 3340, 3347, 3355, 3365, 3374, 3379, 3381, 3381, 3384, 3391, 3398, 3404, 3406, 3407, 3408, 3408, 3409, 3414, 3415, 3416, 3416, 3415, 3414, 3415, 3413, 3416, 3415, 3415, 3414, 3414, 3415, 3416, 3420, 3424, 3428, 3428, 3428, 3431, 3435, 3440, 3442, 3440, 3440, 3440, 3439, 3438, 3435, 3435, 3434, 3436, 3436, 3436, 3436, 3437, 3440, 3442, 3447, 3449, 3450, 3454, 3457, 3455, 3455, 3458, 3459, 3466, 3471, 3483, 3490, 3495, 3499, 3499, 3505, 3508, 3513, 3513, 3511, 3509, 3506, 3502, 3501, 3494, 3491, 3480, 3467, 3459, 3455, 3448, 3446, 3440, 3438, 3435, 3430, 3429, 3424, 3421, 3420, 3417, 3418, 3416, 3416, 3416, 3416, 3418, 3421, 3420, 3422, 3421, 3422, 3420, 3421, 3420, 3418, 3419, 3421, 3423, 3421, 3419, 3414, 3411, 3412, 3410, 3404};
//uint16_t bVec[] = {2785, 2797, 2802, 2797, 2797, 2795, 2797, 2795, 2798, 2809, 2822, 2834, 2838, 2841, 2842, 2839, 2835, 2831, 2831, 2832, 2837, 2841, 2845, 2847, 2848, 2849, 2846, 2847, 2847, 2849, 2848, 2852, 2859, 2865, 2870, 2868, 2870, 2864, 2861, 2866, 2874, 2879, 2890, 2896, 2893, 2893, 2894, 2895, 2897, 2897, 2892, 2884, 2877, 2867, 2858, 2849, 2833, 2820, 2818, 2820, 2824, 2822, 2816, 2806, 2802, 2799, 2790, 2775, 2752, 2739, 2736, 2741, 2743, 2744, 2741, 2738, 2736, 2736, 2737, 2738, 2737, 2734, 2733, 2729, 2724, 2724, 2723, 2723, 2721, 2719, 2721, 2723, 2725, 2724, 2719, 2715, 2713, 2711, 2710, 2708, 2705, 2697, 2694, 2691, 2685, 2684, 2680, 2673, 2667, 2662, 2660, 2655, 2649, 2639, 2628, 2619, 2614, 2608, 2601, 2595, 2583, 2573, 2559, 2541, 2531, 2516, 2496, 2486, 2475, 2466, 2454, 2440, 2422, 2409, 2396, 2379, 2365, 2347, 2336, 2312, 2290, 2267, 2243, 2229, 2211, 2193, 2169, 2150, 2123, 2091, 2055, 2034, 2006, 1961, 1930, 1908, 1882, 1872, 1855, 1825, 1797, 1773, 1743, 1722, 1697, 1670, 1645, 1608, 1585, 1560, 1530, 1505, 1469, 1443, 1404, 1378, 1343, 1282, 1243, 1205, 1176, 1135, 1093, 1056, 1017, 993, 970, 932, 883, 855, 825, 804, 776, 743, 695, 644, 607, 577, 543, 516, 480, 447, 423, 400, 378, 365, 353, 347, 340, 338, 336, 332, 334, 329, 327, 327, 324, 323, 322, 322, 318, 317, 315, 314, 313, 311, 311, 309, 310, 307, 307, 306, 306, 303, 303, 303, 301, 303, 301, 300, 300, 299, 301, 299, 299, 298, 298, 298, 296, 297, 296, 295, 294, 294, 293, 292, 292, 290, 289, 288, 288, 288, 288, 287, 286, 286, 285, 285, 285, 284, 284, 284, 284, 284, 284, 284, 283, 283, 283, 283, 282, 281, 282, 283, 283, 282, 282, 282, 281, 283, 281, 281, 282, 280, 281, 281, 279, 280, 280, 281, 279, 280, 279, 280, 280, 279, 280, 281, 280, 279, 280, 280, 279, 280, 279, 280, 282, 281, 282, 282, 282, 283, 282, 282, 283, 283, 283, 284, 284, 283, 283, 284, 286, 285, 285, 285, 285, 287, 287, 287, 286, 287, 289, 288, 290, 289, 291, 292, 291, 292, 293, 293, 294, 294, 295, 295, 296, 296, 296, 297, 298, 298, 300, 300, 300, 301, 303, 304, 304, 307, 307, 309, 312, 314, 313, 316, 317, 318, 319, 322, 323, 326, 328, 328, 330, 331, 335, 336, 340, 343, 348, 352, 355, 360, 362, 368, 372, 380, 391, 405, 418, 431, 440, 454, 465, 483, 511, 539, 560, 592, 620, 655, 676, 715, 754, 795, 829, 890, 920, 957, 1016, 1060, 1099, 1129, 1155, 1189, 1242, 1283, 1320, 1353, 1369, 1392, 1401, 1426, 1455, 1497, 1520, 1542, 1564, 1585, 1610, 1632, 1669, 1696, 1730, 1773, 1795, 1811, 1874, 1921, 1950, 1973, 2002, 2026, 2058, 2090, 2126, 2151, 2169, 2185, 2190, 2207, 2229, 2269, 2299, 2318, 2333, 2346, 2352, 2361, 2375, 2386, 2407, 2432, 2449, 2458, 2486, 2508, 2516, 2515, 2522, 2536, 2551, 2571, 2592, 2601, 2608, 2608, 2614, 2616, 2630, 2640, 2650, 2660, 2670, 2676, 2680, 2686, 2692, 2697, 2699, 2700, 2703, 2705, 2721, 2740, 2748, 2754, 2759, 2760, 2769, 2781};

//uint16_t aVec[] = {991, 997, 1002, 1006, 1014, 1019, 1024, 1031, 1042, 1048, 1054, 1059, 1063, 1070, 1076, 1079, 1082, 1094, 1100, 1109, 1117, 1121, 1130, 1138, 1152, 1164, 1169, 1177, 1191, 1208, 1229, 1250, 1266, 1288, 1319, 1344, 1361, 1380, 1394, 1409, 1420, 1431, 1443, 1453, 1466, 1474, 1483, 1490, 1500, 1508, 1516, 1522, 1536, 1546, 1557, 1567, 1580, 1599, 1623, 1635, 1656, 1680, 1705, 1721, 1736, 1752, 1765, 1780, 1791, 1804, 1819, 1832, 1841, 1839, 1859, 1876, 1897, 1910, 1928, 1947, 1958, 1972, 1994, 2004, 2033, 2061, 2084, 2102, 2131, 2164, 2190, 2222, 2252, 2279, 2303, 2325, 2350, 2377, 2407, 2422, 2438, 2453, 2472, 2500, 2523, 2536, 2554, 2564, 2577, 2593, 2612, 2630, 2648, 2667, 2684, 2700, 2725, 2748, 2772, 2793, 2808, 2825, 2838, 2853, 2872, 2892, 2903, 2914, 2925, 2934, 2953, 2981, 3003, 3013, 3029, 3034, 3047, 3060, 3076, 3090, 3098, 3112, 3123, 3134, 3145, 3152, 3162, 3171, 3180, 3193, 3200, 3214, 3223, 3229, 3233, 3240, 3247, 3258, 3270, 3274, 3277, 3280, 3285, 3289, 3298, 3305, 3312, 3316, 3328, 3333, 3341, 3345, 3350, 3352, 3356, 3359, 3362, 3365, 3369, 3374, 3375, 3382, 3385, 3391, 3394, 3392, 3395, 3398, 3388, 3374, 3357, 3368, 3403, 3409, 3410, 3413, 3418, 3421, 3423, 3420, 3420, 3419, 3422, 3421, 3420, 3422, 3421, 3420, 3422, 3420, 3420, 3417, 3416, 3416, 3418, 3416, 3418, 3419, 3421, 3424, 3428, 3431, 3432, 3437, 3441, 3446, 3448, 3455, 3460, 3468, 3481, 3490, 3495, 3501, 3502, 3507, 3510, 3512, 3514, 3511, 3507, 3502, 3499, 3497, 3491, 3487, 3475, 3469, 3461, 3459, 3455, 3454, 3457, 3455, 3451, 3449, 3448, 3443, 3440, 3438, 3436, 3436, 3436, 3436, 3435, 3435, 3435, 3438, 3439, 3440, 3440, 3440, 3442, 3440, 3435, 3429, 3428, 3428, 3427, 3423, 3419, 3416, 3414, 3413, 3414, 3415, 3415, 3415, 3413, 3414, 3415, 3416, 3416, 3416, 3414, 3411, 3408, 3408, 3407, 3406, 3405, 3400, 3393, 3384, 3381, 3380, 3380, 3370, 3360, 3351, 3343, 3336, 3330, 3320, 3312, 3307, 3303, 3298, 3294, 3290, 3287, 3282, 3272, 3266, 3258, 3251, 3248, 3244, 3235, 3221, 3206, 3198, 3190, 3174, 3164, 3156, 3141, 3129, 3117, 3104, 3095, 3086, 3076, 3069, 3061, 3055, 3049, 3038, 3027, 3016, 3009, 2994, 2984, 2974, 2961, 2944, 2923, 2898, 2884, 2871, 2848, 2830, 2813, 2783, 2761, 2734, 2711, 2687, 2673, 2651, 2640, 2629, 2614, 2602, 2592, 2572, 2552, 2535, 2506, 2490, 2471, 2454, 2431, 2407, 2365, 2334, 2312, 2288, 2270, 2249, 2231, 2208, 2183, 2165, 2144, 2132, 2116, 2103, 2098, 2081, 2072, 2062, 2043, 2028, 2014, 1994, 1979, 1963, 1948, 1936, 1919, 1899, 1867, 1849, 1830, 1814, 1801, 1781, 1767, 1744, 1727, 1704, 1684, 1668, 1652, 1640, 1631, 1614, 1599, 1579, 1563, 1550, 1530, 1514, 1498, 1480, 1463, 1445, 1421, 1404, 1382, 1375, 1362, 1352, 1341, 1332, 1321, 1312, 1303, 1291, 1282, 1272, 1263, 1257, 1246, 1228, 1219, 1209, 1197, 1185, 1175, 1162, 1147, 1136, 1119, 1102, 1086, 1070, 1067, 1057, 1047, 1040, 1034, 1026, 1017, 1008, 999, 990, 985, 979, 975, 970, 961, 956, 953, 946, 941, 936, 928, 932, 924, 919, 915, 915, 914, 915, 917, 918, 923, 929, 931, 936, 942, 954, 957, 964, 964, 968, 976, 981, 986, 989};
//uint16_t bVec[] = {1036, 1070, 1110, 1152, 1194, 1226, 1262, 1319, 1360, 1396, 1434, 1460, 1497, 1524, 1556, 1582, 1604, 1641, 1668, 1699, 1725, 1744, 1778, 1802, 1838, 1864, 1875, 1892, 1918, 1948, 1985, 2020, 2047, 2074, 2110, 2145, 2164, 2190, 2207, 2225, 2239, 2262, 2283, 2308, 2331, 2346, 2361, 2379, 2395, 2408, 2422, 2430, 2450, 2462, 2473, 2483, 2492, 2507, 2529, 2538, 2553, 2569, 2582, 2593, 2599, 2608, 2613, 2620, 2629, 2638, 2652, 2658, 2661, 2661, 2668, 2675, 2681, 2684, 2688, 2692, 2695, 2701, 2707, 2708, 2711, 2712, 2715, 2716, 2723, 2725, 2724, 2721, 2718, 2720, 2723, 2723, 2724, 2724, 2728, 2732, 2734, 2736, 2738, 2737, 2736, 2736, 2738, 2741, 2744, 2743, 2741, 2735, 2740, 2755, 2777, 2791, 2800, 2803, 2810, 2820, 2823, 2824, 2818, 2818, 2825, 2842, 2852, 2863, 2874, 2881, 2889, 2896, 2898, 2896, 2894, 2893, 2893, 2896, 2889, 2879, 2873, 2866, 2860, 2865, 2871, 2870, 2867, 2861, 2854, 2850, 2848, 2848, 2846, 2847, 2848, 2848, 2847, 2845, 2840, 2837, 2832, 2834, 2830, 2832, 2836, 2840, 2842, 2840, 2836, 2833, 2819, 2804, 2796, 2796, 2797, 2797, 2798, 2798, 2801, 2802, 2798, 2794, 2789, 2788, 2786, 2784, 2786, 2786, 2790, 2802, 2799, 2798, 2781, 2771, 2760, 2755, 2748, 2740, 2723, 2705, 2702, 2700, 2700, 2696, 2690, 2687, 2679, 2676, 2669, 2660, 2654, 2643, 2632, 2620, 2610, 2608, 2610, 2601, 2592, 2571, 2559, 2538, 2526, 2516, 2516, 2509, 2486, 2457, 2449, 2431, 2404, 2385, 2373, 2360, 2350, 2344, 2329, 2312, 2287, 2254, 2216, 2198, 2186, 2179, 2156, 2138, 2098, 2075, 2037, 2011, 1985, 1958, 1934, 1889, 1823, 1798, 1780, 1738, 1703, 1673, 1637, 1613, 1588, 1567, 1544, 1520, 1497, 1455, 1426, 1402, 1390, 1367, 1351, 1318, 1280, 1233, 1179, 1150, 1124, 1090, 1052, 998, 946, 913, 875, 816, 777, 738, 699, 667, 640, 603, 577, 548, 527, 494, 474, 457, 445, 433, 422, 409, 396, 379, 370, 365, 369, 358, 353, 350, 345, 341, 337, 337, 334, 331, 330, 327, 328, 326, 323, 322, 319, 318, 317, 315, 313, 312, 311, 307, 307, 305, 304, 303, 301, 300, 300, 300, 298, 298, 296, 297, 296, 295, 294, 296, 295, 294, 293, 293, 293, 292, 291, 291, 290, 289, 289, 289, 288, 287, 287, 286, 287, 285, 286, 286, 284, 286, 285, 283, 283, 284, 284, 283, 283, 283, 282, 282, 283, 282, 281, 281, 281, 281, 280, 280, 279, 279, 280, 280, 280, 280, 280, 280, 280, 279, 280, 279, 279, 281, 280, 280, 280, 280, 281, 279, 282, 281, 281, 283, 281, 282, 282, 282, 283, 282, 282, 281, 282, 283, 283, 283, 283, 284, 284, 285, 284, 284, 284, 284, 285, 285, 285, 286, 287, 288, 287, 287, 288, 289, 290, 292, 293, 293, 294, 294, 295, 296, 296, 297, 298, 298, 299, 299, 300, 300, 301, 300, 302, 302, 303, 302, 303, 303, 306, 306, 308, 307, 310, 309, 311, 311, 313, 314, 316, 318, 320, 323, 323, 324, 326, 327, 329, 334, 332, 336, 338, 341, 346, 347, 353, 359, 375, 393, 417, 442, 474, 510, 538, 574, 602, 637, 690, 740, 777, 807, 827, 859, 893, 941, 974, 999};
//
//constexpr int vecSize = sizeof(aVec) / sizeof(aVec[0]);

void OpticalEncoderHandler::updatePosition()
{
    uint16_t start = micros();

    uint16_t a = sensor1.getValue();
    uint16_t b = sensor2.getValue();

    int stepSize = static_cast<int>(aVec.size() / 2.0 + 1);

    int i = 0;
    uint32_t cost = calcCost(i, a, b);

    int bestI = i;
    uint32_t bestCost = cost;

    i += stepSize;
    while (i < aVec.size())
    {
        cost = calcCost(i, a, b);

        if (cost < bestCost)
        {
            bestI = i;
            bestCost = cost;
        }

        i += stepSize;
    }

    int checkDir = 1;

    while (stepSize != 1)
    {
        i = bestI;

        stepSize = stepSize / 2;
        if (stepSize == 0)
        {
            stepSize = 1;
        }

        i += stepSize * checkDir;

        cost = calcCost(i, a, b);

        if (cost < bestCost)
        {
            bestI = i;
            bestCost = cost;

            checkDir *= -1;

            continue;
        }

        i -= 2 * stepSize * checkDir;

        cost = calcCost(i, a, b);

        if (cost < bestCost)
        {
            bestI = i;
            bestCost = cost;
        }
    }

    debugValue = micros() - start;

    float newValue = bestI * (4096.0 / aVec.size());

    if (newValue - value > 4096 / 2)
    {
        wrapAroundCorretion -= 4096;
    }
    else if (newValue - value < -4096 / 2)
    {
        wrapAroundCorretion += 4096;
    }

    value = newValue;
}

uint32_t OpticalEncoderHandler::calcCost(int& i, uint16_t a, uint16_t b)
{
    if (i >= aVec.size())
    {
        i -= aVec.size();
    }
    else if (i < 0)
    {
        i += aVec.size();
    }

    uint32_t tempA;
    tempA = aVec[i] - a;
    tempA = tempA * tempA;

    uint32_t tempB;
    tempB = bVec[i] - b;
    tempB = tempB * tempB;

    return tempA + tempB;
}
