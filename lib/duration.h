
enum class chrono_scale : uint32_t {
    nanoseconds = 1,
    milliseconds,
    seconds,
    minutes,
    hours,
    days,
    weeks
};

struct _cpp_chrono_duration {
    chrono_scale _scale;
    uint32_t _num;    // TODO should be in a table indexed by _scale
    uint32_t _den;    // TODO should be in a table indexed by _scale
    int64_t _ticks;   // TODO should be "double"
};

#define CPP_CHRONO_DURATION(v) (*((_cpp_chrono_duration**) Data_custom_val(v)))

extern "C" {
// value cpp_duration_mk_ns(value n);
void mk_duration(value &res, _cpp_chrono_duration const &d);
}