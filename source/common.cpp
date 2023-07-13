#include "common.h"

namespace cpp2
{
    
cmdline_processor::register_flag::register_flag(
    int              group,
    std::string_view name,
    std::string_view description,
    callback0        handler0,
    callback1        handler1,
    std::string_view synonym,
    bool             opt_out
)
{
    cmdline().add_flag( group, name, description, handler0, handler1, synonym, opt_out );
}

} // namespace cpp2