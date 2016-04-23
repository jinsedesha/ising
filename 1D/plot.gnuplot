set term pngcairo
set output "ising.png"
unset key
set xlabel "T [J]"
set ylabel "<E>/N [J]"
plot "plot.dat" with lines, \
     "data.dat" with errorbars
