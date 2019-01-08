# pokemonGO-pokeFinder

<p>Description:
The objective of the program is to find the shortest route to capture all pokemon
given from the keyboard and calculate the minimum distance to be able to get to 
all pokemon with unqiue names and come back to the origin. My program has a class 
pokemon() to hold al of the pokemons location, name, order, distance, and visited.
I find the distance from (0,0) to all pokemon and run my branch and bound function
on each pokemon as the first pokemon. It will then generate the shortest route and 
have my class pokeTrainer() move to those spots and visited them. Finally, return the 
total distance travled, pushes it into a min priority queue and returns the lowest 
route distance. </p>
