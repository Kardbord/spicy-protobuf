#!/usr/bin/env bash

set -e
set -o pipefail

# Working directory
WD="$(dirname "${BASH_SOURCE[0]}")/../build"

FROM_SCRATCH=0
UNIT_TESTS=0
CMAKE_ARGS=("-DCMAKE_EXPORT_COMPILE_COMMANDS=ON")
MAKE_ARGS=()

function usage() {
  echo "${0##*/}"
  echo
  echo "USAGE"
  echo "${0##*/} [-h] [-s] [-t] [-m ARG [-m ARG]...] [-c ARG [-c ARG]...]"
  echo
  echo "This is a helper script for building this project."
  echo
  echo "OPTIONS"
  echo "-h -- Prints this usage message."
  echo "-s -- Performs the build from scratch."
  echo "-t -- Build and run unit tests."
  echo "-m ARG -- Specifies an argument to pass to make (or ninja, if it is available). Can be specified multiple times."
  echo "-c ARG -- Specifies an argument to pass to cmake. Can be specified multiple times."
}

function process_args() {
  while getopts ":m:c:hste" opt; do
    case "${opt}" in
      m)
        MAKE_ARGS+=("${OPTARG}")
        ;;
      c)
        CMAKE_ARGS+=("${OPTARG}")
        ;;
      s)
        FROM_SCRATCH=1
        ;;
      h)
        usage
        exit 0
        ;;
      t)
        UNIT_TESTS=1
        CMAKE_ARGS+=("-DSPICY_PROTOBUF_TEST=ON")
        ;;
      *)
        usage
        exit 1
    esac
  done
  shift $((OPTIND-1))
}

function get_builder {
  if command -v ninja >/dev/null; then
    echo "ninja"
  elif command -v make >/dev/null; then
    echo "make"
  else
    echo "No build tool found. Please install either 'make' or 'ninja'." >&2
    exit 1
  fi
}

function build {
  local builder=$(get_builder)
  [[ "${builder}" = "ninja" ]] && CMAKE_ARGS+=(-GNinja)

  if [[ "${FROM_SCRATCH}" = 1 ]]; then
    #shellcheck disable=SC2046
    rm -rf $(find . -not -name 'README.md' -not -name '.' -not -name '..')
  fi
  #shellcheck disable=SC2048,2086
  cmake ${CMAKE_ARGS[*]} ..
  #shellcheck disable=SC2048,2086
  "${builder}" ${MAKE_ARGS[*]}
  if [[ "${UNIT_TESTS}" = 1 ]]; then
    pushd "testing/gtest"
    ctest --progress
    #pushd "../testing/btest" >/dev/null
    #btest -c btest.cfg
    #popd >/dev/null
  fi
}

function main {
  mkdir -p "${WD}"
  pushd "${WD}" >/dev/null
  process_args "${@}"
  build
  popd >/dev/null
}

main "${@}"
