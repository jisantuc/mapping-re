[@bs.new] [@bs.module "react-leaflet"] [@react.component]
external map:
  (~center: (float, float), ~zoom: int, ~children: array(React.element)) =>
  React.element =
  "Map";

[@react.component]
let make = (~position: (float, float), ~zoom: int) => {
  let child =
    <TileLayer
      url="https://a.tile.openstreetmap.org/${z}/${x}/${y}.png https://b.tile.openstreetmap.org/${z}/${x}/${y}.png"
      attribution="&copy; <a href=&quot;http://osm.org/copyright&quot;>OpenStreetMap</a> contributors"
    />;
  map({"center": position, "zoom": zoom, "children": [|child|]});
};