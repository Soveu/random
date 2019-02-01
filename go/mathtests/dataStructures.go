package main

// a struct holding data of a sub question
type subExercise struct {
	Number       string
	HasVariables bool
	Variables    map[string]string
	Answer       string
}

// a struct holding data for one test question
type exercise struct {
	Name         string
	HasVariables bool
	Subs         []subExercise
}

//a struct holding all the questions
type test struct {
	Questions []exercise
}
