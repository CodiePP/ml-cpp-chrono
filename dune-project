(lang dune 3.4)

(name mlcpp_chrono)

(generate_opam_files true)

(source
 (github CodiePP/ml-cpp-chrono))

(authors "Alexander Diemand <codieplusplus@apax.net>")

(maintainers "Alexander Diemand <codieplusplus@apax.net>")

(license LICENSE)

(documentation https://url/to/documentation)

(package
 (name mlcpp_chrono)
 (synopsis "OCaml embedded C++ time and date handling")
 (description "C++ chrono is a cross-platform abstraction of time and date handling now available in OCaml")
 (depends ocaml dune)
 (tags
  (topics "cross-platform time and date abstraction" your project)))
