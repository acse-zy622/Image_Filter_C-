/**
 * @file main.cpp
 * @brief Main function for the image processing tests.
 *
 * This file contains the main function for the image processing tests, which runs the unit tests for the filtering functions.
 *
 * Group Members:
 * - Hang Zhao (edsml-hz822)
 * - Luwen Liang (edsml-ll2822)
 * - Elliott Mcquire (acse-ecm22)
 * - Zhuoran Yang (acse-zy622)
 * - Qingyang Lu (acse-ql1522)
 */

#include "ImageProcessingTests.h"
#include <iostream>

int main() {
    // Create an ImageProcessingTests object to run the tests
    ImageProcessingTests tests;
    bool all_tests_passed = true;

    // Helper lambda function to run tests and handle exceptions
    auto run_test = [&](const std::string& test_name, auto test_func) {
        try {
            test_func();
            std::cout << test_name << " test passed." << std::endl;
        } catch (const std::exception& e) {
            std::cerr << test_name << " test failed: " << e.what() << std::endl;
            all_tests_passed = false;
        }
    };

    // Run the tests for various image processing functions
    std::cout << "Running Median blur test..." << std::endl;
    run_test("Median blur", [&]() { tests.test_median_blur(); });

    std::cout << "Running Box blur test..." << std::endl;
    run_test("Box blur", [&]() { tests.test_box_blur(); });

    std::cout << "Running Gaussian blur test..." << std::endl;
    run_test("Gaussian blur", [&]() { tests.test_gaussian_blur(); });

    std::cout << "Running Apply gray scale test..." << std::endl;
    run_test("Apply gray scale", [&]() { tests.test_apply_gray_scale(); });

    std::cout << "Running Auto colour balance test..." << std::endl;
    run_test("Auto colour balance", [&]() { tests.test_auto_colour_balance(); });

    std::cout << "Running Brightness test..." << std::endl;
    run_test("Brightness", [&]() { tests.test_brightness(); });

    std::cout << "Running Sobel detection test..." << std::endl;
    run_test("Sobel detection", [&]() { tests.test_sobel_edge_detection(); });

    std::cout << "Running Prewitt detection test..." << std::endl;
    run_test("Prewitt detection", [&]() { tests.test_prewitt_edge_detection(); });

    std::cout << "Running 3d median blur test..." << std::endl;
    run_test("3d median blur", [&]() { tests.test_median_blur_3d(); });

    std::cout << "Running 3d gaussian blur test..." << std::endl;
    run_test("3d gaussian blur", [&]() { tests.test_gaussian_blur_3d(); });

    return all_tests_passed ? 0 : 1;
}