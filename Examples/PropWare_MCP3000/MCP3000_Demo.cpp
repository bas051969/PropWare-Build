/**
 * @file    MCP3000_Demo.cpp
 *
 * @author  David Zemon
 *
 * @copyright
 * The MIT License (MIT)<br>
 * <br>Copyright (c) 2013 David Zemon<br>
 * <br>Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:<br>
 * <br>The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.<br>
 * <br>THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <PropWare/PropWare.h>
#include <PropWare/printer/printer.h>
#include <PropWare/mcp3000.h>

/** Used for determining the bit-width of the ADC channel (10, 12, or 13 bit) */
const PropWare::MCP3000::PartNumber PART_NUMBER = PropWare::MCP3000::MCP300x;
const PropWare::MCP3000::Channel    CHANNEL     = PropWare::MCP3000::CHANNEL_1;

/** Pin number for MOSI (master out - slave in) */
const PropWare::Port::Mask MOSI = PropWare::Port::P0;
/** Pin number for MISO (master in - slave out) */
const PropWare::Port::Mask MISO = PropWare::Port::P1;
/** Pin number for the clock signal */
const PropWare::Port::Mask SCLK = PropWare::Port::P2;
/** Pin number for chip select */
const PropWare::Port::Mask CS   = PropWare::Port::P3;

/**
 * @example     MCP3000_Demo.cpp
 *
 * Continuously read the ADC value from a channel of the MCP3000 and print it to the terminal.
 *
 * @include PropWare_MCP3000/CMakeLists.txt
 */
int main () {
    const uint16_t    DIVISOR = 1024 / 8;
    uint16_t          data = 0;
    uint32_t          loopCounter;
    uint8_t           scaledValue, i;
    uint32_t          ledOutput;
    PropWare::SPI     spi(MOSI, MISO, SCLK);
    PropWare::MCP3000 adc(&spi, CS, PART_NUMBER);

    // Set the Quickstart LEDs for output (used as a secondary display)
    PropWare::SimplePort scale(PropWare::Port::P16, 8, PropWare::Pin::OUT);

    // Though this functional call is not necessary (default value is 0), I
    // want to bring attention to this function. It will determine whether the
    // adc.read* functions will always explicitly set the SPI modes before
    // each call, or assume that the SPI cog is still running in the proper
    // configuration
    adc.always_set_spi_mode(0);

    pwOut << "Welcome to the MCP3000 demo!\n";

    while (1) {
        loopCounter = SECOND / 2 + CNT;

        // Loop over the LED output very quickly, until we are within 1
        // millisecond of total period
        while (abs(loopCounter - CNT) > MILLISECOND) {
            data = adc.read(CHANNEL);

            // Turn on LEDs proportional to the analog value
            scaledValue = (uint8_t) ((data + DIVISOR / 2 - 1) / DIVISOR);
            ledOutput   = 0;
            for (i      = 0; i < scaledValue; ++i)
                ledOutput = (ledOutput << 1) | 1;
            scale.write(ledOutput);
        }

        pwOut.printf("Channel %d is reading: %d\n", CHANNEL, data);
    }
}