#include <thrax/stringfst.h>

#include <thrax/function.h>

DEFINE_string(initial_boundary_symbol, "BOS",
              "Predefined symbol to mark beginning of string.");
DEFINE_string(final_boundary_symbol, "EOS",
              "Predefined symbol to mark end of string.");

DEFINE_int64(generated_label_start_index, 0x100000,
             "The first index to use for a generated label.");
DEFINE_int64(generated_label_end_index, 0x10fffb,
             "The last index to use for a generated label.");
DEFINE_int64(initial_boundary_marker, 0x10fffc,
             "Marker for the beginning of a string.");
DEFINE_int64(final_boundary_marker, 0x10fffd,
             "Marker for the end of a string.");

