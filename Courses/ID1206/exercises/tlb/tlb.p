set terminal png
set output "tlb.png"

set title "TLB benchmark, 4 KiByte pages, 10 Gi operations"

set key right center

set xlabel "number of pages"
set ylabel "time in s"

#use logscale if we use doubling of number of pages
set logscale x 2

plot "tlb4K.dat" u 1:2 w linespoints title "page refs", \
     "tlb64.dat" u 1:2 w linespoints title "page size 64 bytes", \
     "dummy4K.dat" u 1:2 w linespoints title "dummy4K", \
     "dummy64.dat" u 1:2 w linespoints title "dummy64"
