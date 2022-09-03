
type cpp_duration
type duration =
    Nanoseconds of cpp_duration
  | Milliseconds of cpp_duration
  | Seconds of cpp_duration
  | Minutes of cpp_duration
  | Hours of cpp_duration
  | Days of cpp_duration
  | Weeks of cpp_duration

module Duration = struct
    external cpp_duration_to_int : cpp_duration -> int = "cpp_duration_to_int"

    let to_string = function
        Nanoseconds n  -> (string_of_int @@ cpp_duration_to_int n) ^ " ns"
      | Milliseconds n -> (string_of_int @@ cpp_duration_to_int n) ^ " ms"
      | Seconds n      -> (string_of_int @@ cpp_duration_to_int n) ^ " s"
      | Minutes n      -> (string_of_int @@ cpp_duration_to_int n) ^ " m"
      | Hours n        -> (string_of_int @@ cpp_duration_to_int n) ^ " h"
      | Days n         -> (string_of_int @@ cpp_duration_to_int n) ^ " d"
      | Weeks n        -> (string_of_int @@ cpp_duration_to_int n) ^ " w"

    let to_int = function
        Nanoseconds n  -> cpp_duration_to_int n
      | Milliseconds n -> cpp_duration_to_int n
      | Seconds n      -> cpp_duration_to_int n
      | Minutes n      -> cpp_duration_to_int n
      | Hours n        -> cpp_duration_to_int n
      | Days n         -> cpp_duration_to_int n
      | Weeks n        -> cpp_duration_to_int n

    external cpp_int_to_ns : int -> cpp_duration = "cpp_duration_mk_ns"
    let int_to_ns n = Nanoseconds (cpp_int_to_ns n)
    external cpp_int_to_ms : int -> cpp_duration = "cpp_duration_mk_ms"
    let int_to_ms n = Milliseconds (cpp_int_to_ms n)
    external cpp_int_to_s : int -> cpp_duration = "cpp_duration_mk_s"
    let int_to_s n = Seconds (cpp_int_to_s n)
    external cpp_int_to_m : int -> cpp_duration = "cpp_duration_mk_m"
    let int_to_m n = Minutes (cpp_int_to_m n)
    external cpp_int_to_h : int -> cpp_duration = "cpp_duration_mk_h"
    let int_to_h n = Hours (cpp_int_to_h n)
    external cpp_int_to_d : int -> cpp_duration = "cpp_duration_mk_d"
    let int_to_d n = Days (cpp_int_to_d n)
    external cpp_int_to_w : int -> cpp_duration = "cpp_duration_mk_w"
    let int_to_w n = Weeks (cpp_int_to_w n)

    let to_cpp_duration = function
        Nanoseconds n  -> n
      | Milliseconds n -> n
      | Seconds n      -> n
      | Minutes n      -> n
      | Hours n        -> n
      | Days n         -> n
      | Weeks n        -> n

    external cpp_cast_to_ns : cpp_duration -> cpp_duration = "cpp_cast_to_ns"
    let cast_ns n = Nanoseconds (cpp_cast_to_ns @@ to_cpp_duration n)
    external cpp_cast_to_ms : cpp_duration -> cpp_duration = "cpp_cast_to_ms"
    let cast_ms n = Milliseconds (cpp_cast_to_ms @@ to_cpp_duration n)
    external cpp_cast_to_s : cpp_duration -> cpp_duration = "cpp_cast_to_s"
    let cast_s n = Seconds (cpp_cast_to_s @@ to_cpp_duration n)
    external cpp_cast_to_m : cpp_duration -> cpp_duration = "cpp_cast_to_m"
    let cast_m n = Minutes (cpp_cast_to_m @@ to_cpp_duration n)
    external cpp_cast_to_h : cpp_duration -> cpp_duration = "cpp_cast_to_h"
    let cast_h n = Hours (cpp_cast_to_h @@ to_cpp_duration n)
    external cpp_cast_to_d : cpp_duration -> cpp_duration = "cpp_cast_to_d"
    let cast_d n = Days (cpp_cast_to_d @@ to_cpp_duration n)
    external cpp_cast_to_w : cpp_duration -> cpp_duration = "cpp_cast_to_w"
    let cast_w n = Weeks (cpp_cast_to_w @@ to_cpp_duration n)

    let eq d1 d2 = (to_int @@ cast_ns d1) = (to_int @@ cast_ns d2)
    let lt d1 d2 = (to_int @@ cast_ns d1) < (to_int @@ cast_ns d2)
    let le d1 d2 = (to_int @@ cast_ns d1) <= (to_int @@ cast_ns d2)
    let gt d1 d2 = not @@ le d1 d2
    let ge d1 d2 = not @@ lt d1 d2

    let add d1 d2 = int_to_ns ((to_int @@ cast_ns d1) + (to_int @@ cast_ns d2))
end (* Duration *)

(*
type 'a timepoint = int
module Timepoint = struct
    let to_time_t _tp = 0
    let eq _tp1 _tp2 = false
    let lt _tp1 _tp2 = true
    let le _tp1 _tp2 = true
    let gt tp1 tp2 = not @@ le tp1 tp2
    let ge tp1 tp2 = not @@ lt tp1 tp2
end (* Timepoint *)
*)

module Clock = struct

module type CLOCK =
sig
    type timepoint
    val now : unit -> timepoint
    (* val from_time_t : int -> t *)
    val to_sys_time : timepoint -> float
    val diff : timepoint -> timepoint -> duration
end

module System : CLOCK = struct
    type timepoint 
    external now : unit -> timepoint = "cpp_system_clock_now"
    external to_sys_time : timepoint -> float = "cpp_system_clock_get"
    external cpp_diff : timepoint -> timepoint -> cpp_duration = "cpp_system_clock_diff"
    let diff tp1 tp2 = Nanoseconds (cpp_diff tp1 tp2)
end (* System_clock *)

module Steady : CLOCK = struct
    type timepoint
    external now : unit -> timepoint = "cpp_steady_clock_now"
    external to_sys_time : timepoint -> float = "cpp_steady_clock_get"
    external cpp_diff : timepoint -> timepoint -> cpp_duration = "cpp_steady_clock_diff"
    let diff tp1 tp2 = Nanoseconds (cpp_diff tp1 tp2)
end (* Steady_clock *)

module Hires : CLOCK = struct
    type timepoint
    external now : unit -> timepoint = "cpp_hires_clock_now"
    external to_sys_time : timepoint -> float = "cpp_hires_clock_get"
    external cpp_diff : timepoint -> timepoint -> cpp_duration = "cpp_hires_clock_diff"
    let diff tp1 tp2 = Nanoseconds (cpp_diff tp1 tp2)
end (* Hires_clock *)

end (* Clock *)