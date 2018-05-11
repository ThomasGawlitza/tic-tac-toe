type gridCellT =
  | X
  | O
  | Empty;

type t('a) = 
  | WhoAmI : t(unit)
  | YouAre : t(gridCellT)
  | Checked : t((gridCellT, int));

let stringify (type a, x: t(a)) = switch (x) {
  | WhoAmI => "WhoAmI"
  | YouAre  => "YouAre"
  | Checked => "Checked"
  };