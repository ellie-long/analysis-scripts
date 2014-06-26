#!/bin/csh

foreach i ( kees_gen.C kees_gepgmp.C kees_gmngd.C kees_gmpgd.C )
root -q -b HallA_style.cxx $i+
end
