
[@react.component]
let make = () => {
  let center = ((-75.1652), 39.9526);
  let zoom = 13;

  <div
    style={ReactDOMRe.Style.make(
      ~background="burlywood",
      ~flex="1",
      ~flexShrink="0",
      (),
    )}>
    <Map position={center} zoom={zoom} />
  </div>;
};