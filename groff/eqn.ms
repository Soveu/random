.TL
Formatting Math Equations with groff and eqn
.AU
Luke Smith
.PP
Here is nome paragraph text.
This all will be processed by groff.
The command to compile it goes like that:

.cw
.ce 2
.br
.I "eqn filename.ms -T pdf | groff -ms -T pdf > output.pdf"
.br
.I "groff -e filename.ms -ms -T pdf > output.pdf"
.br

But we can process a block of code with eqn by putting it between .EQ and .EN.
.EQ
x != 3 + 5
.EN
.EQ
Delta x >= 3 +- 5
.EN
.EQ
b sup 2 - 4ac
.EN
.EQ
b sup {2 - 4ac}
.EN
.EQ
phi = {1 + sqrt 5} over 2
.EN
.EQ
x = 
sqrt {
sum from i=1 to { N + 5 }
}
.EN
.EQ
x = 
sqrt {
sum from i=1 to N ( x sub i - x bar ) sup 2
}
.EN
