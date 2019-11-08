[@react.component]
let make = () => {
    <header style={ReactDOMRe.Style.make
        (~background="lightslategray",
         ~height="50px",
          ~width="100%",
           ~flexShrink="0", ())}>{React.string("Franklin's Dunk Squad")}</header>;
};