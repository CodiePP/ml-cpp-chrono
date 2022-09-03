
type duration

module Duration :
sig
    val to_string : duration -> string
    val to_int : duration -> int
    (* TODO  val ticks : duration -> float *)
    val int_to_ns : int -> duration
    val int_to_ms : int -> duration
    val int_to_s : int -> duration
    val int_to_m : int -> duration
    val int_to_h : int -> duration
    val int_to_d : int -> duration
    val int_to_w : int -> duration
    val cast_ns : duration -> duration
    val cast_ms : duration -> duration
    val cast_s  : duration -> duration
    val cast_m  : duration -> duration
    val cast_h  : duration -> duration
    val cast_d  : duration -> duration
    val cast_w  : duration -> duration
    val eq : duration -> duration -> bool
    val lt : duration -> duration -> bool
    val le : duration -> duration -> bool
    val gt : duration -> duration -> bool
    val ge : duration -> duration -> bool
    val add : duration -> duration -> duration
end

module Clock :
sig

module type CLOCK =
sig
    type timepoint
    val now : unit -> timepoint
    val to_sys_time : timepoint -> float
    (* compatible with Unix.time : seconds since 00:00 Jan-1 1970 *)
    val diff : timepoint -> timepoint -> duration
    (* returns the duration in nanoseconds *)

end

module System : CLOCK

module Steady : CLOCK

module Hires : CLOCK

end (* Clock *)