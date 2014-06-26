#!/usr/bin/perl -w

while( <> ) {
  ($v1,$v2) = split;
  printf("%.10f   %.10f\n",$v1,$v2);
}
