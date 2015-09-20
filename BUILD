cc_library(
  name = "framework",
  srcs = ["framework.cc"],
  hdrs = ["framework.h", "mcmc.h"],
  deps = [":logger"]
)

cc_library(
  name = "logger",
  srcs = ["logger.cc"],
  hdrs = ["logger.h"],
)

cc_library(
  name = "histogram",
  srcs = ["histogram.cc"],
  hdrs = ["histogram.h"],
)

cc_library(
  name = "impl",
  srcs = ["impl.cc"],
  hdrs = ["impl.h"],
)

cc_binary(
  name = "client",
  srcs = ["client.cc"],
  deps = [
    ":impl",
    ":framework",
    ":histogram"
  ],
)

cc_binary(
  name = "test_histogram",
  srcs = ["test_histogram.cc"],
  deps = [
    ":histogram"
  ],
)
