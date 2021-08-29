signalNoise <- function(vec){
  n <- length(vec)
  rowMax = max(vec);
  noiseMax = sort(vec, partial = n-1)[n-1];
  return(rowMax/noiseMax);
}