
// std::chrono::system_clock

struct _cpp_chrono_system_clock;

#define CPP_CHRONO_SYSTEM_CLOCK(v) (*((_cpp_chrono_system_clock**) Data_custom_val(v)))


// std::chrono::steady_clock

struct _cpp_chrono_steady_clock;

#define CPP_CHRONO_STEADY_CLOCK(v) (*((_cpp_chrono_steady_clock**) Data_custom_val(v)))


// std::chrono::high_resolution_clock

struct _cpp_chrono_hires_clock;

#define CPP_CHRONO_HIRES_CLOCK(v) (*((_cpp_chrono_hires_clock**) Data_custom_val(v)))
