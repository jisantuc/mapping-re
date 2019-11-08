[@react.component]
let make = () => {
  <div
    style={ReactDOMRe.Style.make(
      ~background="burlywood",
      ~flex="1",
      ~flexShrink="0",
      (),
    )}>
    {React.string("MAP GOES HERE")}
  </div>;
};