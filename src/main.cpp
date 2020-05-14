int main(int argc, char* argv[]) {
  try {
    const auto beg = std::chrono::high_resolution_clock::now();
    std::vector<int> v(1'000);

    std::for_each(v.begin(), v.end(), [&](auto& e) {
      std::this_thread::sleep_for(std::chrono::milliseconds{ 1 });
      e = argc;
    });

    const auto end = std::chrono::high_resolution_clock::now();
    fmt::print("{} ns\n", std::chrono::floor<std::chrono::nanoseconds>(end - beg));
  }
  catch (const std::exception& e) {
    fmt::print(stderr, "error: {}\n", e.what());
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
