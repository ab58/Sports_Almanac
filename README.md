# The Ultimate Sports Almanac

This program enables a user to look up the career stats of any player in the history of any of the 4 major
North American professional sports (Football, Hockey, Baseball, and Basketball). Data is pulled from the
reference websites hosted on the sports-reference.com network. This app makes use of the libcurl library
for C and C++. Source code is in C++. For details on the data see:

https://www.sports-reference.com/

https://www.pro-football-reference.com/

https://www.hockey-reference.com/

https://www.baseball-reference.com/

https://www.basketball-reference.com/

Upon starting, the user is prompted to enter a name of any player. Search is performed by full last name, 
partial last name, full first plus partial last name, or full first plus full last name. In cases of multiple
matches for a player search, a numbered list of names is provided, followed by the players' years played, their
position (if available), and the league/sport they play(ed) in. The user is then prompted to enter the desired 
player by number, and keeps being prompted until a valid number is entered. Career statistics are displayed for
the player, pulled from the first table on the player page of the relevant sports-reference website. Subsequently
the user is asked if they would like to continue or quit, and if they choose to continue the app loops around again
and the process repeats. Pressing 'q' to quit terminates the program after a completed process of retrieving player stats.

As of right now, only the player's "most relevant stats" are displayed, i.e. the group of statistics that is most 
relevant to the player's position and/or career. For example a quarterback will have only passing stats displayed but
not his rushing stats (which are displayed in a secondary table below the primary stats table on his web page), or a 
pitcher will only have his pitching stats displayed and not his batting stats (which are likewise displayed separately 
in a secondary table on the web page). Subsequent releases of this project will aim to ask followup requests to the user
for what stats they desire (such as informing the user that passing and rushing stats are available for a quarterback, and
which group they would like to see, or likewise for pitching/batting for a pitcher).

Other ideas for expansion of the Almanac include asking the user for a specific year in the player's career that they would
like to see stats for, i.e. the ability to view single-season stats as well, either for just a single year or a range of years.
Another idea would be to be able to display "partial career stats", i.e. take a range of years from a player's career and add up
the single-season statistics and get summed up stats for only that range of seasons.
