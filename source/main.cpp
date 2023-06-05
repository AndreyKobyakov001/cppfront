#include "common.h"
#include "cppfront.h"

//===========================================================================
//  main - driver
//===========================================================================

using namespace std;
using namespace cpp2;

static auto enable_debug_output_files = false;
static cmdline_processor::register_flag cmd_debug(
    9,
    "debug",
    "Emit compiler debug output files",
    []{ enable_debug_output_files = true; }
);



auto main(
    int   argc,
    char* argv[]
)
    -> int
{
    cmdline().set_args(argc, argv);
    cmdline().process_flags();

    if (cmdline().help_was_requested()) {
        return EXIT_SUCCESS;
    }

    if (cmdline().arguments().empty()) {
        std::cerr << "cppfront: error: no input files (try -help)\n";
        return EXIT_FAILURE;
    }

    //  For each Cpp2 source file
    int exit_status = EXIT_SUCCESS;
    for (auto const& arg : cmdline().arguments())
    {
        std::cout << arg.text << "...";

        //  Load + lex + parse + sema
        cppfront c(arg.text);

        //  Generate Cpp1 (this may catch additional late errors)
        auto count = c.lower_to_cpp1();

        //  If there were no errors, say so and generate Cpp1
        if (c.had_no_errors())
        {
            if (!c.has_cpp1()) {
                std::cout << " ok (all Cpp2, passes safety checks)\n";
            }
            else if (c.has_cpp2()) {
                std::cout << " ok (mixed Cpp1/Cpp2, Cpp2 code passes safety checks)\n";
            }
            else {
                std::cout << " ok (all Cpp1)\n";
            }

            if (flag_verbose) {
                std::cout << "   Cpp1: " << count.cpp1_lines << " lines\n";
                std::cout << "   Cpp2: " << count.cpp2_lines << " lines";
                if (count.cpp1_lines + count.cpp2_lines > 0) {
                    std::cout << " (" << 100 * count.cpp2_lines / (count.cpp1_lines + count.cpp2_lines) << "%)";
                }
                std::cout << "\n";
            }

            std::cout << "\n";
        }
        //  Otherwise, print the errors
        else
        {
            std::cerr << "\n";
            c.print_errors();
            std::cerr << "\n";
            exit_status = EXIT_FAILURE;
        }

        //  In any case, emit the debug information (during early development this is
        //  on by default, later we'll flip the switch to turn it on instead of off)
        if (enable_debug_output_files) {
            c.debug_print();
        }
    }
    return exit_status;
}
