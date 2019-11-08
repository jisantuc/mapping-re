[@bs.val] external fetch: string => Js.Promise.t('a) = "fetch";

type state =
  | LoadingCollection
  | CollectionLoadError
  | LoadedCollection(string, string);

[@react.component]
let make = () => {
  let (state, setState) = React.useState(() => LoadingCollection);

  React.useEffect0(() => {
    Js.Promise.(
      fetch(
        "http://localhost:9090/collections/e54a18e8-9992-47f3-923f-4adfe383f0dc",
      )
      |> then_(response => response##json())
      |> then_(jsonResponse => {
           setState(_previousState =>
             LoadedCollection(jsonResponse##license, jsonResponse##version)
           );
           Js.Promise.resolve();
         })
      |> catch(_err => {
           setState(_previousState => CollectionLoadError);
           Js.Promise.resolve();
         })
      |> ignore
    );

    None;
  });

  <div
    style={
      ReactDOMRe.Style.make(
        ~background="coral",
        ~width="300px",
        ~overflow="auto",
        ~padding="0 15px 15px",
        ~height="100%",
        (),
      )
    }>
    {
      switch (state) {
      | LoadingCollection => React.string("Loading...")
      | CollectionLoadError =>
        React.string("Can't read collection from source, turn your server on")
      | LoadedCollection(license, version) =>
        <div>
          <div> {React.string("License is: ")} {React.string(license)} </div>
          <div> {React.string("Version is: ")} {React.string(version)} </div>
        </div>
      }
    }
  </div>;
};
