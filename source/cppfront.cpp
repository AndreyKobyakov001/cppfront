
//  Copyright (c) Herb Sutter
//  SPDX-License-Identifier: CC-BY-NC-ND-4.0

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.


//===========================================================================
//  cppfront
//===========================================================================

#include "cppfront.h"

namespace cpp2 {

cmdline_processor& cmdline() { 
    static auto* cmd = new cmdline_processor;
    return *cmd;
}

//  Defined out of line here just to avoid bringing <iostream> into the headers,
//  so that we can't accidentally start depending on iostreams in the compiler body
auto cmdline_processor::print(std::string_view s, int width)
    -> void
{
    if (width > 0) {
        std::cout << std::setw(width) << std::left;
    }
    std::cout << s;
}


} //namespace cpp2
