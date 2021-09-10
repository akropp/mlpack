/**
 * @file mlpack_main.hpp
 * @author Ryan Curtin
 *
 * Define the macros used when compiling a Julia binding.  This file should not
 * be included directly; instead, mlpack/core/util/mlpack_main.hpp should be
 * included with the right setting of BINDING_TYPE.
 */
#ifndef MLPACK_BINDINGS_JULIA_MLPACK_MAIN_HPP
#define MLPACK_BINDINGS_JULIA_MLPACK_MAIN_HPP

#ifndef BINDING_TYPE
  #error "BINDING_TYPE not defined!  Don't include this file directly!"
#endif
#if BINDING_TYPE != BINDING_TYPE_JL
  #error "BINDING_TYPE is not set to BINDING_TYPE_JL!"
#endif

// Matrices are transposed on load/save.
#define BINDING_MATRIX_TRANSPOSED true

#include <mlpack/bindings/julia/julia_option.hpp>
#include <mlpack/bindings/julia/print_doc_functions.hpp>

/**
 * PRINT_PARAM_STRING() returns a string that contains the correct
 * language-specific representation of a parameter's name.
 */
#define PRINT_PARAM_STRING mlpack::bindings::julia::ParamString

/**
 * PRINT_PARAM_VALUE() returns a string that contains a correct
 * language-specific representation of a parameter's value.
 */
#define PRINT_PARAM_VALUE mlpack::bindings::julia::PrintValue

/**
 * PRINT_DATASET() returns a string that contains a correct language-specific
 * representation of a dataset name.
 */
#define PRINT_DATASET mlpack::bindings::julia::PrintDataset

/**
 * PRINT_MODEL() returns a string that contains a correct language-specific
 * representation of an mlpack model name.
 */
#define PRINT_MODEL mlpack::bindings::julia::PrintModel

/**
 * PRINT_CALL() returns a string that contains the full language-specific
 * representation of a call to an mlpack binding.  The first argument should be
 * the name of the binding, and all other arguments should be names of
 * parameters followed by values (in the case where the preceding parameter is
 * not a flag).
 */
#define PRINT_CALL mlpack::bindings::julia::ProgramCall

/**
 * BINDING_IGNORE_CHECK() is an internally-used macro to determine whether or
 * not a specific parameter check should be ignored.
 */
#define BINDING_IGNORE_CHECK(...) mlpack::bindings::julia::IgnoreCheck( \
    STRINGIFY(BINDING_NAME), __VA_ARGS__)

namespace mlpack {
namespace util {

template<typename T>
using Option = mlpack::bindings::julia::JuliaOption<T>;

}
}

#include <mlpack/core/util/param.hpp>

// In Julia, we want to call the binding function mlpack_<BINDING_NAME>()
// instead of just <BINDING_NAME>(), so we change the definition of
// BINDING_FUNCTION().
#undef BINDING_FUNCTION
#define BINDING_FUNCTION(...) JOIN(mlpack_, BINDING_NAME)(__VA_ARGS__)

// Add default parameters that are included in every program.
PARAM_GLOBAL(bool, "verbose", "Display informational messages and the full "
    "list of parameters and timers at the end of execution.", "v", "bool",
    false, true, false, false);

#endif