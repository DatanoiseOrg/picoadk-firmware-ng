#pragma once

static inline int32_t float_to_int32(float input) {
    // Simple conversion from float to int32
    // This assumes that the input float is within the range that can be
    // represented by int32. Typically, audio samples are normalized between
    /// -1.0 and 1.0, so we multiply by the max int32 value
    int32_t output;

    if (input >= 1.0f) {
        output = INT32_MAX;
    } else if (input <= -1.0f) {
        output = INT32_MIN;
    } else {
        output = static_cast<int32_t>(input) * static_cast<float>(INT32_MAX);
    }

    return output;
}
