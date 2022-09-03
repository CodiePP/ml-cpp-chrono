(* open Mlcpp_clock *)

let () =
  let open Alcotest in
  run "ML Cpp Chrono" [
    TestDuration.test;
    (* TestClock.test; *)
  ]