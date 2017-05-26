Algorithm Used:

1. Read the data from the file passed through command line argument.

2. Store the data in suitable data structures.

3. Set action and value to any arbitrary value, here set to 0.

4. Then run the policy evaluation for all the states till it converges:
	a. Calculate the value of each states by: Sum(For all state: transition probability(S,A,S') * (Reward for (S,A, S') * discount_Factor + value of state(S'))).

	b. Repeat step 4 until it converges to a value by comparing the difference between previous and current value of all states with a small delta value to check the convergence, until all the previous and current state value differences became less than the delta value [Here .000000001].

5. Then run policy iteration on given State and Action set. 
	a. For all State and action, calculate the state value using all the possible action for a state to find that if a better function value exists using any action as the action value. Same formula (4b) has been used.

	b. If we find a better state value using any other action for a state other than the current one, then repeat step 4 and 5, until there is no change in the action value after performing the policy iteration.

6. If there is no change after performing the policy iteraion, i.e. the action state pair given by the last policy evaluation is optimal, then that one is the solution.

7. Print the state value and action in proper format.
