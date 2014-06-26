TGraph *readfile(const char* filename,int col1=1, int col2=2) {
  Double_t x,y;
  FILE *fp = fopen(filename,"r");
  if (!fp) {
    Error("readfile","Cannot open file %s.",filename);
    return 0;
  }
    
  TGraph *gr = new TGraph(1);
  char line[100];
  Int_t np = 0;

  TString format;
  int maxcol = (col1>col2 ? col1 : col2);
  for (int i=1; i<=maxcol; i++) {
    if (i==col1 || i==col2) {
      format += Form(" %%lg");
    } else {
      format += Form(" %%*lg");
    }
  }
  
  cout << "using format of " << format.Data() << endl;
  while (fgets(line,100,fp)) {
    if (line[0]=='#') continue;
    sscanf(&line[0],format.Data(),&x, &y);
    gr->SetPoint(np,x,y);
    np++;
  }
  return gr;
}

void build_spline_file(const char* filename,int col1=1, int col2=2) {
  // read in the file, and build a spline interpolation of it,
  // writing it out to <filename>.spl3
  // write out points every .05 from 0. to 10.


  TGraph *gr = readfile(filename,col1,col2);
  TCanvas *c1 = new TCanvas("c1");
  c1->cd();
  gr->Draw("ap");
  c1->Update();
  TSpline3 spl("spline",gr);
  Double_t dx=0.05;
  TString outf(filename);
  outf+=".spl3";
  outf+="\0";
  ofstream to(outf.Data());
  for (Double_t x=0.; x<10.; x+=dx) {
    to.form("%6.3g   %6g\n",x,spl.Eval(x));
  }
  to.close();
  //  delete gr;
}

  
