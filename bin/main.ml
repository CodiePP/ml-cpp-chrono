
open Mlcpp_chrono

let millions_of_clocks () =
    for i = 0 to 1000000 do
        Chrono.Clock.System.now () |> Chrono.Clock.System.to_sys_time |> fun t -> (Int.to_float i) *. t |> ignore
    done

let () =
    let d1 = Chrono.Duration.int_to_d 42 in
    Printf.printf "a duration: %s\n" (Chrono.Duration.to_string d1);
    let sysclock1 = Chrono.Clock.System.now () in
    Printf.printf "system clock since 1970: %f\n" (Chrono.Clock.System.to_sys_time sysclock1);

    let steadyclock = Chrono.Clock.Steady.now () in
    Printf.printf "steady clock since 1970: %f\n" (Chrono.Clock.Steady.to_sys_time steadyclock);
    let hiresclock = Chrono.Clock.Hires.now () in
    Printf.printf "hires clock since 1970: %f\n" (Chrono.Clock.Hires.to_sys_time hiresclock);
    let t = Unix.time () in
    Printf.printf "system time: %f\n" t;

    let sysclock2 = Chrono.Clock.System.now () in
    Printf.printf "system clock since 1970: %f\n" (Chrono.Clock.System.to_sys_time sysclock2);
    let d2 = Chrono.Clock.System.diff sysclock2 sysclock1 in 
    Printf.printf "system clock duration = %s\n" (Chrono.Duration.to_string d2);

    millions_of_clocks ();

    let sysclock3 = Chrono.Clock.System.now () in
    Printf.printf "system clock since 1970: %f\n" (Chrono.Clock.System.to_sys_time sysclock3);
    let d3 = Chrono.Clock.System.diff sysclock3 sysclock2 in 
    Printf.printf "system clock duration = %s\n" (Chrono.Duration.to_string d3);
    let d4 = Chrono.Duration.add d2 d3 in
    Printf.printf "Total duration = %s\n" (Chrono.Duration.to_string d4);
