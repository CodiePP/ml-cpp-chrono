open Mlcpp_chrono

module Testing = struct
  let to_string = Chrono.Duration.to_string
  let cast_to_ns = fun d -> Chrono.Duration.to_int @@ Chrono.Duration.cast_ns d
  let cast_to_ms = fun d -> Chrono.Duration.to_int @@ Chrono.Duration.cast_ms d
  let cast_to_s = fun d -> Chrono.Duration.to_int @@ Chrono.Duration.cast_s d
  let cast_to_m = fun d -> Chrono.Duration.to_int @@ Chrono.Duration.cast_m d
  let cast_to_h = fun d -> Chrono.Duration.to_int @@ Chrono.Duration.cast_h d
  let cast_to_d = fun d -> Chrono.Duration.to_int @@ Chrono.Duration.cast_d d
  let cast_to_w = fun d -> Chrono.Duration.to_int @@ Chrono.Duration.cast_w d
  let eq = Chrono.Duration.eq
  let lt = Chrono.Duration.lt
  let le = Chrono.Duration.le
  let gt = Chrono.Duration.gt
  let ge = Chrono.Duration.ge
  let add = Chrono.Duration.add
end

(* Tests *)

let test_to_string_ns () =
  Alcotest.(check string)
  "string representation of [ns] duration"
  "42 ns" (* == *) (Testing.to_string @@ Chrono.Duration.int_to_ns 42)
let test_to_string_ms () =
  Alcotest.(check string)
  "string representation of [ms] duration"
  "42 ms" (* == *) (Testing.to_string @@ Chrono.Duration.int_to_ms 42)
let test_to_string_s () =
  Alcotest.(check string)
  "string representation of [s] duration"
  "42 s" (* == *) (Testing.to_string @@ Chrono.Duration.int_to_s 42)
let test_to_string_m () =
  Alcotest.(check string)
  "string representation of [m] duration"
  "42 m" (* == *) (Testing.to_string @@ Chrono.Duration.int_to_m 42)
let test_to_string_h () =
  Alcotest.(check string)
  "string representation of [h] duration"
  "42 h" (* == *) (Testing.to_string @@ Chrono.Duration.int_to_h 42)
let test_to_string_d () =
  Alcotest.(check string)
  "string representation of [d] duration"
  "42 d" (* == *) (Testing.to_string @@ Chrono.Duration.int_to_d 42)
let test_to_string_w () =
  Alcotest.(check string)
  "string representation of [w] duration"
  "42 w" (* == *) (Testing.to_string @@ Chrono.Duration.int_to_w 42)

let test_cast_to_ns () =
  Alcotest.(check int)
  "cast of duration to [ns]"
  42000000 (* == *) (Testing.cast_to_ns @@ Chrono.Duration.int_to_ms 42)
let test_cast_to_ms () =
  Alcotest.(check int)
  "cast of duration to [ms]"
  39600000 (* == *) (Testing.cast_to_ms @@ Chrono.Duration.int_to_h 11)
let test_cast_ms_to_m () =
  Alcotest.(check int)
  "cast of duration to [m]"
  2 (* == *) (Testing.cast_to_m @@ Chrono.Duration.int_to_ms 120000)
let test_cast_m_to_s () =
  Alcotest.(check int)
  "cast of duration to [s]"
  660 (* == *) (Testing.cast_to_s @@ Chrono.Duration.int_to_m 11)
let test_cast_h_to_s () =
  Alcotest.(check int)
  "cast of duration to [s]"
  3600 (* == *) (Testing.cast_to_s @@ Chrono.Duration.int_to_h 1)
let test_cast_h_to_h () =
  Alcotest.(check int)
  "cast of duration to [h]"
  12 (* == *) (Testing.cast_to_h @@ Chrono.Duration.int_to_h 12)
let test_cast_m_to_h () =
  Alcotest.(check int)
  "cast of duration to [h]"
  0 (* == *) (Testing.cast_to_h @@ Chrono.Duration.int_to_m 33)
let test_cast_to_d () =
  Alcotest.(check int)
  "cast of duration to [d]"
  2 (* == *) (Testing.cast_to_d @@ Chrono.Duration.int_to_h 48)
let test_cast_to_w () =
  Alcotest.(check int)
  "cast of duration to [w]"
  4 (* == *) (Testing.cast_to_w @@ Chrono.Duration.int_to_d 30)

let test_eq () =
  Alcotest.(check bool)
  "comparison: eq"
  true @@
  Testing.eq (Chrono.Duration.int_to_h (24 * 30)) (Chrono.Duration.int_to_d 30)

let test_lt () =
  Alcotest.(check bool)
  "comparison: lt"
  true @@
  Testing.lt (Chrono.Duration.int_to_s 3) (Chrono.Duration.int_to_ms 4000)

let test_le () =
  Alcotest.(check bool)
  "comparison: le"
  true @@
  Testing.le (Chrono.Duration.int_to_s 3) (Chrono.Duration.int_to_ms 3000)

let test_gt () =
  Alcotest.(check bool)
  "comparison: gt"
  true @@
  Testing.gt (Chrono.Duration.int_to_m 3) (Chrono.Duration.int_to_ns 300000000)

let test_ge () =
  Alcotest.(check bool)
  "comparison: ge"
  true @@
  Testing.ge (Chrono.Duration.int_to_d 365) (Chrono.Duration.int_to_w 52)

let test_add () =
  Alcotest.(check int)
  "add durations"
  (Chrono.Duration.to_int @@ Chrono.Duration.cast_ns @@ Chrono.Duration.int_to_ms (3000 + 4000))
  (* == *)
  (Chrono.Duration.to_int @@ Testing.add (Chrono.Duration.int_to_s 3) (Chrono.Duration.int_to_ms 4000))


(* Runner *)

let test =
  let open Alcotest in
  "ML Cpp Chrono.Duration",
  [
    test_case "string representation" `Quick test_to_string_ns;
    test_case "string representation" `Quick test_to_string_ms;
    test_case "string representation" `Quick test_to_string_s;
    test_case "string representation" `Quick test_to_string_m;
    test_case "string representation" `Quick test_to_string_h;
    test_case "string representation" `Quick test_to_string_d;
    test_case "string representation" `Quick test_to_string_w;
    test_case "cast ms -> ns" `Quick test_cast_to_ns;
    test_case "cast h -> ms" `Quick test_cast_to_ms;
    test_case "cast m -> s" `Quick test_cast_m_to_s;
    test_case "cast h -> s" `Quick test_cast_h_to_s;
    test_case "cast ms -> m" `Quick test_cast_ms_to_m;
    test_case "cast h -> h" `Quick test_cast_h_to_h;
    test_case "cast h -> d" `Quick test_cast_to_d;
    test_case "cast d -> w" `Quick test_cast_to_w;
    test_case "comparison eq" `Quick test_eq;
    test_case "comparison lt" `Quick test_lt;
    test_case "comparison le" `Quick test_le;
    test_case "comparison gt" `Quick test_gt;
    test_case "comparison ge" `Quick test_ge;
    test_case "add durations" `Quick test_add;
  ]