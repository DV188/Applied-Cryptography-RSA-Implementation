/* The authors of this work have released all rights to it and placed it
in the public domain under the Creative Commons CC0 1.0 waiver
(http://creativecommons.org/publicdomain/zero/1.0/).

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

Retrieved from: http://en.literateprograms.org/Miller-Rabin_primality_test_(C,_GMP)?oldid=18974
*/

#ifndef MILLER_RABIN
#define MILLER_RABIN

#include <gmp.h> //GNU Multiple Precision Arithmetic Library(https://gmplib.org/), used for big numbers.

#define COMPOSITE        0
#define PROBABLE_PRIME   1

int miller_rabin_pass(mpz_t a, mpz_t n);
int miller_rabin(mpz_t n, gmp_randstate_t rand_state);

#endif
