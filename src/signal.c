/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlok <xlok@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 12:25:44 by xlok              #+#    #+#             */
/*   Updated: 2024/10/25 21:40:57 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	sig;

void	handler(int signum)
{
	sig = signum;
	if (sig == SIGQUIT)
	{
//		write(1, "\n", 1);
		rl_on_new_line();
//		rl_replace_line("", 0);
		rl_redisplay();
//		return ;
	}
	else if (sig == SIGINT)
		write(1, "SIGINT\n", 7);
//		code;

//	rl_on_new_line();
//	rl_replace_line("hello", 0);
//	rl_redisplay();
}

void	ft_signal(void)
{
	struct sigaction	sa;

	sa.sa_handler = handler;
//	sa.sa_handler = SIG_IGN;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
//	signal(SIGQUIT, SIG_IGN);
	if (sigaction(SIGQUIT, &sa, 0) == -1)
		perror("signal handler error");//
//	if (sigaction(SIGINT, &sa, 0) == -1)
//		perror("signal handler error");//
}

/*
If you use readline() in a signal handler registered with sigaction(), you can run into issues. The readline() function (like many other I/O functions) is not reentrant and should not be called from within a signal handler. Doing so can lead to undefined behavior, including data corruption or program crashes.

Key Points
Signal Handlers: Signal handlers are executed asynchronously when a signal is caught. Because of this, you should avoid using functions that can modify state or rely on global data (like readline()) within a signal handler.

Safe Functions: If you need to handle signals, use functions that are async-signal-safe, such as write(), signal(), or exit(). For anything that requires complex behavior (like reading input), it's better to set a flag in the signal handler and handle the reading logic in the main loop.

Example
Here’s an example showing how to handle a signal without directly calling readline() in the signal handler:

c
Copy code
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <readline/readline.h>

volatile sig_atomic_t got_signal = 0;

void signal_handler(int sig) {
    got_signal = 1; // Set a flag when the signal is received
}

int main() {
    struct sigaction sa;
    sa.sa_handler = signal_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    // Register the signal handler for SIGINT (Ctrl+C)
    sigaction(SIGINT, &sa, NULL);

    while (1) {
        if (got_signal) {
            got_signal = 0; // Reset the flag
            printf("Signal received! You can now enter a line.\n");
        }

        // Read input safely
        char *line = readline("Enter something: ");
        if (line) {
            printf("You entered: %s\n", line);
            free(line);
        }
    }

    return 0;
}
Explanation:
Signal Handling: A signal handler sets a flag (got_signal) when a SIGINT (like Ctrl+C) is received.
Main Loop: The main loop checks for the signal flag and prompts the user for input using readline().
Avoiding readline() in Handler: readline() is only called in the main loop, not in the signal handler, preventing any potential issues.
This way, you ensure that your program remains stable while still handling signals appropriately.

In the context of using the GNU Readline library, rl_done is a flag that indicates whether a read operation is complete, allowing you to manage input in a more flexible way, especially when dealing with signals. However, rl_done is not part of the standard interface and is typically used internally by Readline.

Using rl_done
If you are working with a signal handler and want to gracefully interrupt readline() when a signal occurs, you can set the rl_done flag. Here's how you can use it:

Setup Signal Handling: You would set up a signal handler that sets rl_done to a non-zero value to interrupt Readline when a signal is caught.
Check for rl_done: In your main loop, after calling readline(), you can check the rl_done flag to determine if the input operation was interrupted.
Example
Here's a simple example demonstrating this:

c
Copy code
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>

void signal_handler(int sig) {
    rl_done = 1;  // Indicate that readline should stop
}

int main() {
    struct sigaction sa;
    sa.sa_handler = signal_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    // Register the signal handler for SIGINT (Ctrl+C)
    sigaction(SIGINT, &sa, NULL);

    while (1) {
        rl_done = 0; // Reset the flag before reading

        char *line = readline("Enter something: ");
        if (line) {
            if (rl_done) {
                printf("\nInput interrupted by signal.\n");
                free(line);
                continue;  // Optionally handle the interruption
            }

            printf("You entered: %s\n", line);
            free(line);
        } else {
            printf("No input received.\n");
            break; // Handle EOF or error
        }
    }

    return 0;
}
Explanation:
Signal Handling: The signal handler sets rl_done to 1 when a signal is caught.
Reading Input: Before calling readline(), rl_done is reset to 0. After readline() returns, you check rl_done to see if the input was interrupted.
Handling Interruption: If rl_done is set, you can handle it accordingly, like printing a message or skipping to the next iteration of the loop.
Caveats
Non-Reentrant Functions: Although using rl_done can help manage signals, be aware that you should still avoid using non-reentrant functions in the signal handler itself.
Behavior of Readline: Depending on the version of the Readline library you are using, the behavior of rl_done may vary, so be sure to consult the documentation for your specific version.
Using rl_done in conjunction with proper signal handling can help you make your command-line applications more responsive to user interruptions.

Yes, using rl_on_new_line, rl_replace_line, and rl_redisplay can help manage the behavior of Readline in response to signals or other events, though they serve different purposes compared to rl_done. Here’s how you can use these functions effectively:

Functions Overview
rl_on_new_line: This function can be used to indicate that you are starting a new line of input. It is useful when you want to manipulate the line being edited, particularly if you need to reset some state or display information.

rl_replace_line: This function replaces the current line in the input buffer without affecting the cursor position. You can use it to modify what the user is currently editing or to display messages.

rl_redisplay: This function redraws the current line in the terminal, which can be useful after you have modified the line using rl_replace_line.

Example Scenario
Here’s an example where you can use these functions to manage input behavior more effectively:

c
Copy code
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>

void signal_handler(int sig) {
    // Indicate that the user should be informed about the interruption
    rl_on_new_line();         // Move to a new line
    rl_replace_line("Input interrupted! Please enter again: ", 0);
    rl_redisplay();           // Redraw the line
}

int main() {
    struct sigaction sa;
    sa.sa_handler = signal_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    // Register the signal handler for SIGINT (Ctrl+C)
    sigaction(SIGINT, &sa, NULL);

    while (1) {
        char *line = readline("Enter something: ");
        if (line) {
            printf("You entered: %s\n", line);
            free(line);
        } else {
            printf("No input received. Exiting.\n");
            break; // Handle EOF or error
        }
    }

    return 0;
}
Explanation:
Signal Handling: The signal handler uses rl_on_new_line() to reset the input line and rl_replace_line() to display a message indicating that the input was interrupted.

Redisplay: After replacing the line, rl_redisplay() is called to update the terminal display with the new line.

User Experience: This allows for a smoother user experience, as it informs the user of the interruption without terminating the input process abruptly.

Important Considerations:
Avoid Complex Logic in Handlers: You should avoid putting complex logic or long operations in signal handlers. In this example, we keep it simple by only updating the input line.

Non-Reentrant Functions: Be mindful of using functions that are not safe to call in a signal handler. While the above functions are generally safe, always check the documentation for your specific version of Readline.

Conclusion
Using rl_on_new_line, rl_replace_line, and rl_redisplay can indeed enhance how you handle user input in the presence of signals or other interruptions, making your application more robust and user-friendly.
*/
