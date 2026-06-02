
#include "libft.h"

bool ft_feq(double a, double b) {
  double diff;
  double scale;

  diff = ft_fabs(a - b);
  if (diff < DBL_EPSILON)
    return (true);
  scale = ft_fmax(ft_fabs(a), ft_fabs(b));
  return (diff < DBL_EPSILON * (1.0 + scale));
}
