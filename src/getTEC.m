function TECvect = getTEC (prn, M)
  TECvect=[];
  for i = 1:size(M)(1)
    if (M(i,7)==prn)
      TECvect(end+1) = -9.52*10^16*(M(i,11)-M(i,12));
    endif
  endfor
endfunction