
// OCaml includes
extern "C" {
#include <caml/mlvalues.h>
#include <caml/memory.h>
#include <caml/alloc.h>
#include <caml/custom.h>
// #include <caml/callback.h>
#include <caml/fail.h>
} //extern C

// C++ includes
#include <ctime>
#include <chrono>

#include "chrono.h"
#include "duration.h"

// std::chrono::system_clock

struct _cpp_chrono_system_clock {
    std::chrono::time_point<std::chrono::system_clock> _timepoint;
};

void del_cpp_chrono_system_clock (value v) {
    CAMLparam1(v);
    struct _cpp_chrono_system_clock *s = CPP_CHRONO_SYSTEM_CLOCK(v);
    if (s) {
        // printf("delete timepoint %llx\n", s);
        delete s;
    }
    CAMLreturn0;
}

static struct custom_operations cpp_chrono_system_clock_ops = {
    (char *)"mlcpp_chrono_system_clock",
    del_cpp_chrono_system_clock,
    custom_compare_default,
    custom_hash_default,
    custom_serialize_default,
    custom_deserialize_default
};

void mk_timepoint_system_clock(value &res, _cpp_chrono_system_clock const &s) {
    res = caml_alloc_custom(&cpp_chrono_system_clock_ops,
                            sizeof(_cpp_chrono_system_clock*), 1, 1000);
    auto * cs = new _cpp_chrono_system_clock;
    cs->_timepoint = s._timepoint;
    CPP_CHRONO_SYSTEM_CLOCK(res) = cs;
}

/*
 *   cpp_system_clock_now : unit -> timepoint
 */
extern "C" {
value cpp_system_clock_now(value unit)
{
    CAMLparam1(unit);
    CAMLlocal1(res);
    struct _cpp_chrono_system_clock c {
        std::chrono::system_clock::now()
    };
    mk_timepoint_system_clock(res, c);
    CAMLreturn(res);
}
} // extern C

/*
 *   cpp_system_clock_get : timepoint -> float
 */
extern "C" {
value cpp_system_clock_get(value tp)
{
    CAMLparam1(tp);
    struct _cpp_chrono_system_clock *c = CPP_CHRONO_SYSTEM_CLOCK(tp);
    const auto d = c->_timepoint.time_since_epoch();
    // const auto dns = std::chrono::duration_cast<std::chrono::nanoseconds>(d);
    // double t = dns.count() / 1000000000.0;
    // printf("t since epoch: %lld = %f\n", dns.count(), t);
    value res = caml_alloc(Double_wosize, Double_tag);
    // Store_double_val(res, t);
    Store_double_val(res, (double)std::chrono::duration_cast<std::chrono::nanoseconds>(d).count() / 1000000000.0);
    CAMLreturn(res);
}
} // extern C

/*
 *   cpp_system_clock_diff : timepoint -> timepoint -> duration
 */
extern "C" {
value cpp_system_clock_diff(value tp1, value tp2)
{
    CAMLparam2(tp1, tp2);
    CAMLlocal1(res);
    struct _cpp_chrono_system_clock *c1 = CPP_CHRONO_SYSTEM_CLOCK(tp1);
    struct _cpp_chrono_system_clock *c2 = CPP_CHRONO_SYSTEM_CLOCK(tp2);
    auto dmus = c1->_timepoint - c2->_timepoint;
    auto dns = std::chrono::duration_cast<std::chrono::nanoseconds>(dmus);
    // printf("diff = %lld\n", dns.count());
    struct _cpp_chrono_duration dres {
       chrono_scale::nanoseconds,
       std::chrono::nanoseconds::period::num,
       std::chrono::nanoseconds::period::den,
       (int64_t)(dns.count())
    };
    mk_duration(res, dres);
    CAMLreturn(res);
}
} // extern C


// std::chrono::steady_clock

struct _cpp_chrono_steady_clock {
    std::chrono::time_point<std::chrono::steady_clock> _timepoint;
};

void del_cpp_chrono_steady_clock (value v) {
    CAMLparam1(v);
    struct _cpp_chrono_steady_clock *s = CPP_CHRONO_STEADY_CLOCK(v);
    if (s) {
        //printf("delete timepoint %llx\n", s);
        delete s;
    }
    CAMLreturn0;
}

static struct custom_operations cpp_chrono_steady_clock_ops = {
    (char *)"mlcpp_chrono_steady_clock",
    del_cpp_chrono_steady_clock,
    custom_compare_default,
    custom_hash_default,
    custom_serialize_default,
    custom_deserialize_default
};

void mk_timepoint_steady_clock(value &res, _cpp_chrono_steady_clock const &s) {
    res = caml_alloc_custom(&cpp_chrono_steady_clock_ops,
                            sizeof(_cpp_chrono_steady_clock*), 1, 1000);
    auto * cs = new _cpp_chrono_steady_clock;
    cs->_timepoint = s._timepoint;
    CPP_CHRONO_STEADY_CLOCK(res) = cs;
}

/*
 *   cpp_steady_clock_now : unit -> timepoint
 */
extern "C" {
value cpp_steady_clock_now(value unit)
{
    CAMLparam1(unit);
    CAMLlocal1(res);
    struct _cpp_chrono_steady_clock c {
        std::chrono::steady_clock::now()
    };
    mk_timepoint_steady_clock(res, c);
    CAMLreturn(res);
}
} // extern C

/*
 *   cpp_steady_clock_get : timepoint -> float
 */
extern "C" {
value cpp_steady_clock_get(value tp)
{
    CAMLparam1(tp);
    struct _cpp_chrono_steady_clock *c = CPP_CHRONO_STEADY_CLOCK(tp);
    const auto d = c->_timepoint.time_since_epoch();
    value res = caml_alloc(Double_wosize, Double_tag);;
    Store_double_val(res, (double)std::chrono::duration_cast<std::chrono::nanoseconds>(d).count() / 1000000000.0);
    CAMLreturn(res);
}
} // extern C

/*
 *   cpp_steady_clock_diff : timepoint -> timepoint -> duration
 */
extern "C" {
value cpp_steady_clock_diff(value tp1, value tp2)
{
    CAMLparam2(tp1, tp2);
    CAMLlocal1(res);
    struct _cpp_chrono_steady_clock *c1 = CPP_CHRONO_STEADY_CLOCK(tp1);
    struct _cpp_chrono_steady_clock *c2 = CPP_CHRONO_STEADY_CLOCK(tp2);
    auto dmus = c1->_timepoint - c2->_timepoint;
    auto dns = std::chrono::duration_cast<std::chrono::nanoseconds>(dmus);
    // printf("diff = %lld\n", dns.count());
    struct _cpp_chrono_duration dres {
       chrono_scale::nanoseconds,
       std::chrono::nanoseconds::period::num,
       std::chrono::nanoseconds::period::den,
       (int64_t)(dns.count())
    };
    mk_duration(res, dres);
    CAMLreturn(res);
}
} // extern C


// std::chrono::high_resolution_clock

struct _cpp_chrono_hires_clock {
    std::chrono::time_point<std::chrono::high_resolution_clock> _timepoint;
};

void del_cpp_chrono_hires_clock (value v) {
    CAMLparam1(v);
    struct _cpp_chrono_hires_clock *s = CPP_CHRONO_HIRES_CLOCK(v);
    if (s) {
        //printf("delete timepoint %llx\n", s);
        delete s;
    }
    CAMLreturn0;
}

static struct custom_operations cpp_chrono_hires_clock_ops = {
    (char *)"mlcpp_chrono_hires_clock",
    del_cpp_chrono_hires_clock,
    custom_compare_default,
    custom_hash_default,
    custom_serialize_default,
    custom_deserialize_default
};

void mk_timepoint_hires_clock(value &res, _cpp_chrono_hires_clock const &s) {
    res = caml_alloc_custom(&cpp_chrono_hires_clock_ops,
                            sizeof(_cpp_chrono_hires_clock*), 1, 1000);
    auto * cs = new _cpp_chrono_hires_clock;
    cs->_timepoint = s._timepoint;
    CPP_CHRONO_HIRES_CLOCK(res) = cs;
}

/*
 *   cpp_hires_clock_now : unit -> timepoint
 */
extern "C" {
value cpp_hires_clock_now(value unit)
{
    CAMLparam1(unit);
    CAMLlocal1(res);
    struct _cpp_chrono_hires_clock c {
        std::chrono::high_resolution_clock::now()
    };
    mk_timepoint_hires_clock(res, c);
    CAMLreturn(res);
}
} // extern C

/*
 *   cpp_hires_clock_get : timepoint -> float
 */
extern "C" {
value cpp_hires_clock_get(value tp)
{
    CAMLparam1(tp);
    struct _cpp_chrono_hires_clock *c = CPP_CHRONO_HIRES_CLOCK(tp);
    const auto d = c->_timepoint.time_since_epoch();
    value res = caml_alloc(Double_wosize, Double_tag);;
    Store_double_val(res, (double)std::chrono::duration_cast<std::chrono::nanoseconds>(d).count() / 1000000000.0);
    CAMLreturn(res);
}
} // extern C

/*
 *   cpp_hires_clock_diff : timepoint -> timepoint -> duration
 */
extern "C" {
value cpp_hires_clock_diff(value tp1, value tp2)
{
    CAMLparam2(tp1, tp2);
    CAMLlocal1(res);
    struct _cpp_chrono_hires_clock *c1 = CPP_CHRONO_HIRES_CLOCK(tp1);
    struct _cpp_chrono_hires_clock *c2 = CPP_CHRONO_HIRES_CLOCK(tp2);
    auto dmus = c1->_timepoint - c2->_timepoint;
    auto dns = std::chrono::duration_cast<std::chrono::nanoseconds>(dmus);
    // printf("diff = %lld\n", dns.count());
    struct _cpp_chrono_duration dres {
       chrono_scale::nanoseconds,
       std::chrono::nanoseconds::period::num,
       std::chrono::nanoseconds::period::den,
       (int64_t)(dns.count())
    };
    mk_duration(res, dres);
    CAMLreturn(res);
}
} // extern C
