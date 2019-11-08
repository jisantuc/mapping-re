[@bs.new] [@bs.module "react-map-gl"] [@react.component]
external interactiveMap:
  (~longitude: float, ~latitude: float, ~height: int, ~width: int) =>
  React.element =
  "InteractiveMap";

[@react.component]
let make = (~longitude: float, ~latitude: float) => {
  interactiveMap({"longitude": longitude, "latitude": latitude, "height": 400, "width": 400});
};