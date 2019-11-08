[@react.component]
let make = (~children) =>
  <div
    style={ReactDOMRe.Style.make(
      ~background="blue",
      ~display="flex",
      ~flex="1",
      ~overflowY="auto",
      ~height="100%",
      (),
    )}>
    children
  </div>;