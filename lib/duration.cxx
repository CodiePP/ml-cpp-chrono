
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
#include <chrono>

#include "duration.h"


void del_cpp_chrono_duration (value d) {
    CAMLparam1(d);
    struct _cpp_chrono_duration *duration = CPP_CHRONO_DURATION(d);
    if (duration) {
        // printf("delete duration %llx\n", duration);
        delete duration;
    }
    CAMLreturn0;
}

static struct custom_operations cpp_chrono_ops = {
    (char *)"mlcpp_chrono",
    del_cpp_chrono_duration,
    custom_compare_default,
    custom_hash_default,
    custom_serialize_default,
    custom_deserialize_default
};

void mk_duration(value &res, _cpp_chrono_duration const &d) {
    res = caml_alloc_custom(&cpp_chrono_ops,
                            sizeof(_cpp_chrono_duration*), 1, 100);
    auto * cdur = new _cpp_chrono_duration;
    cdur->_num = d._num;
    cdur->_den = d._den;
    cdur->_scale = d._scale;
    cdur->_ticks = d._ticks;
    CPP_CHRONO_DURATION(res) = cdur;
}

/*
 *   cpp_duration_to_int : duration -> int
 */
extern "C" {
value cpp_duration_to_int(value d)
{
    CAMLparam1(d);
    struct _cpp_chrono_duration *duration = CPP_CHRONO_DURATION(d);
    if (duration) {
        CAMLreturn(Val_long(duration->_ticks));
    } else {
        CAMLreturn(Val_long(-1));
    }
}
} // extern C

extern "C" {
value cpp_duration_mk_ns(value n)
{
    CAMLparam1(n);
    CAMLlocal1(res);
    struct _cpp_chrono_duration d {
       chrono_scale::nanoseconds,
       std::chrono::nanoseconds::period::num,
       std::chrono::nanoseconds::period::den,
       Long_val(n)
    };
    mk_duration(res, d);
    CAMLreturn(res);
}
} // extern C

extern "C" {
value cpp_duration_mk_ms(value n)
{
    CAMLparam1(n);
    CAMLlocal1(res);
    struct _cpp_chrono_duration d {
       chrono_scale::milliseconds,
       std::chrono::milliseconds::period::num,
       std::chrono::milliseconds::period::den,
       Long_val(n)
    };
    mk_duration(res, d);
    CAMLreturn(res);
}
} // extern C

extern "C" {
value cpp_duration_mk_s(value n)
{
    CAMLparam1(n);
    CAMLlocal1(res);
    struct _cpp_chrono_duration d {
       chrono_scale::seconds,
       std::chrono::seconds::period::num,
       std::chrono::seconds::period::den,
       Long_val(n)
    };
    mk_duration(res, d);
    CAMLreturn(res);
}
} // extern C

extern "C" {
value cpp_duration_mk_m(value n)
{
    CAMLparam1(n);
    CAMLlocal1(res);
    struct _cpp_chrono_duration d {
       chrono_scale::minutes,
       std::chrono::minutes::period::num,
       std::chrono::minutes::period::den,
       Long_val(n)
    };
    mk_duration(res, d);
    CAMLreturn(res);
}
} // extern C

extern "C" {
value cpp_duration_mk_h(value n)
{
    CAMLparam1(n);
    CAMLlocal1(res);
    struct _cpp_chrono_duration d {
       chrono_scale::hours,
       std::chrono::hours::period::num,
       std::chrono::hours::period::den,
       Long_val(n)
    };
    mk_duration(res, d);
    CAMLreturn(res);
}
} // extern C

extern "C" {
value cpp_duration_mk_d(value n)
{
    CAMLparam1(n);
    CAMLlocal1(res);
    struct _cpp_chrono_duration d {
       chrono_scale::days,
       std::chrono::hours::period::num * 24L,
       std::chrono::hours::period::den,
       Long_val(n)
    };
    mk_duration(res, d);
    CAMLreturn(res);
}
} // extern C

extern "C" {
value cpp_duration_mk_w(value n)
{
    CAMLparam1(n);
    CAMLlocal1(res);
    struct _cpp_chrono_duration d {
       chrono_scale::weeks,
       std::chrono::hours::period::num * 24L * 7L,
       std::chrono::hours::period::den,
       Long_val(n)
    };
    mk_duration(res, d);
    CAMLreturn(res);
}
} // extern C


extern "C" {
value cpp_cast_to_ns(value v)
{
    CAMLparam1(v);
    CAMLlocal1(res);
    uint32_t tnum = std::chrono::nanoseconds::period::num;
    uint32_t tden = std::chrono::nanoseconds::period::den;
    auto num = CPP_CHRONO_DURATION(v)->_num;
    double fnum = (double)num / tnum;
    auto den = CPP_CHRONO_DURATION(v)->_den;
    double fden = (double)tden / den;
    auto ticks = CPP_CHRONO_DURATION(v)->_ticks;
    struct _cpp_chrono_duration d {
       chrono_scale::nanoseconds,
       tnum,
       tden,
       (int64_t)((double)ticks * fnum * fden)
    };
    mk_duration(res, d);
    CAMLreturn(res);
}
} // extern C

extern "C" {
value cpp_cast_to_ms(value v)
{
    CAMLparam1(v);
    CAMLlocal1(res);
    uint32_t tnum = std::chrono::milliseconds::period::num;
    uint32_t tden = std::chrono::milliseconds::period::den;
    auto num = CPP_CHRONO_DURATION(v)->_num;
    double fnum = (double)num / tnum;
    auto den = CPP_CHRONO_DURATION(v)->_den;
    double fden = (double)tden / den;
    auto ticks = CPP_CHRONO_DURATION(v)->_ticks;
    struct _cpp_chrono_duration d {
       chrono_scale::milliseconds,
       tnum,
       tden,
       (int64_t)((double)ticks * fnum * fden)
    };
    mk_duration(res, d);
    CAMLreturn(res);
}
} // extern C

extern "C" {
value cpp_cast_to_s(value v)
{
    CAMLparam1(v);
    CAMLlocal1(res);
    uint32_t tnum = std::chrono::seconds::period::num;
    uint32_t tden = std::chrono::seconds::period::den;
    auto num = CPP_CHRONO_DURATION(v)->_num;
    double fnum = (double)num / tnum;
    auto den = CPP_CHRONO_DURATION(v)->_den;
    double fden = (double)tden / den;
    auto ticks = CPP_CHRONO_DURATION(v)->_ticks;
    struct _cpp_chrono_duration d {
       chrono_scale::seconds,
       tnum,
       tden,
       (int64_t)((double)ticks * fnum * fden)
    };
    mk_duration(res, d);
    CAMLreturn(res);
}
} // extern C

extern "C" {
value cpp_cast_to_m(value v)
{
    CAMLparam1(v);
    CAMLlocal1(res);
    uint32_t tnum = std::chrono::minutes::period::num;
    uint32_t tden = std::chrono::minutes::period::den;
    auto num = CPP_CHRONO_DURATION(v)->_num;
    double fnum = (double)num / tnum;
    auto den = CPP_CHRONO_DURATION(v)->_den;
    double fden = (double)tden / den;
    auto ticks = CPP_CHRONO_DURATION(v)->_ticks;
    struct _cpp_chrono_duration d {
       chrono_scale::minutes,
       tnum,
       tden,
       (int64_t)((double)ticks * fnum * fden)
    };
    mk_duration(res, d);
    CAMLreturn(res);
}
} // extern C

extern "C" {
value cpp_cast_to_h(value v)
{
    CAMLparam1(v);
    CAMLlocal1(res);
    uint32_t tnum = std::chrono::hours::period::num;
    uint32_t tden = std::chrono::hours::period::den;
    auto num = CPP_CHRONO_DURATION(v)->_num;
    double fnum = (double)num / tnum;
    auto den = CPP_CHRONO_DURATION(v)->_den;
    double fden = (double)tden / den;
    auto ticks = CPP_CHRONO_DURATION(v)->_ticks;
    struct _cpp_chrono_duration d {
       chrono_scale::hours,
       tnum,
       tden,
       (int64_t)((double)ticks * fnum * fden)
    };
    mk_duration(res, d);
    CAMLreturn(res);
}
} // extern C

extern "C" {
value cpp_cast_to_d(value v)
{
    CAMLparam1(v);
    CAMLlocal1(res);
    uint32_t tnum = std::chrono::hours::period::num * 24L;
    uint32_t tden = std::chrono::hours::period::den;
    auto num = CPP_CHRONO_DURATION(v)->_num;
    double fnum = (double)num / tnum;
    auto den = CPP_CHRONO_DURATION(v)->_den;
    double fden = (double)tden / den;
    auto ticks = CPP_CHRONO_DURATION(v)->_ticks;
    struct _cpp_chrono_duration d {
       chrono_scale::days,
       tnum,
       tden,
       (int64_t)((double)ticks * fnum * fden)
    };
    mk_duration(res, d);
    CAMLreturn(res);
}
} // extern C

extern "C" {
value cpp_cast_to_w(value v)
{
    CAMLparam1(v);
    CAMLlocal1(res);
    uint32_t tnum = std::chrono::hours::period::num * 24L * 7L;
    uint32_t tden = std::chrono::hours::period::den;
    auto num = CPP_CHRONO_DURATION(v)->_num;
    double fnum = (double)num / tnum;
    auto den = CPP_CHRONO_DURATION(v)->_den;
    double fden = (double)tden / den;
    auto ticks = CPP_CHRONO_DURATION(v)->_ticks;
    struct _cpp_chrono_duration d {
       chrono_scale::weeks,
       tnum,
       tden,
       (int64_t)((double)ticks * fnum * fden)
    };
    mk_duration(res, d);
    CAMLreturn(res);
}
} // extern C