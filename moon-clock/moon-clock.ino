
/*       Moon Clock
 * 
 * A clock with lights showing the current moon phase.
 * 
 * Starts in setup mode.
 * 
 * 
 * ---------------
 *  - Setup Mode:
 * 
 * During setup, we set the clock by pressing the button.
 * 
 * For that, we define how many days have passed since the last new moon, and we press the button that much times.
 * Lights show the current value % 5
 * All lights on: 0
 * Zero light: 5, 10, 15, 20, 25
 * One light: 1, 6, 11, 16, 21, 26
 * ...
 * Resets to 0 after 28 presses.
 * 
 * Example: Last new moon (full black) was on 10 January. We are the 17 January. 7 days passed since new moon. 
 * We press the button 7 times.
 * 
 *
 * Do not press button for 5 seconds to go into clock mode. 
 * 
 * 
 * ---------------
 *  - Clock Mode:
 * 
 * 4 lights: 1 2 3 4
 * 
 * All off: New Moon
 * All on: Full Moon
 * 4 on: Waxing Crescent
 * 3+4 on : First Quarter
 * ...
 * 
 * --
 * TODO
 * 
 * - Take hemisphere in account
 * 
 */
