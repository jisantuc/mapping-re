[@bs.val] [@bs.module "react-leaflet"] [@react.component]
external tileLayer: (~url: string, ~attribution: string) => React.element =
  "TileLayer.createLeafletElement";

[@react.component]
let make = (~url: string, ~attribution: string) => {
  tileLayer({"url": url, "attribution": attribution});
};