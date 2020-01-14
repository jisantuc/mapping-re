// js interop --
// this is done with bindings rather than ports. You have to be
// correct about the js types, or this will go really poorly.
// [@bs.val] external fetch says to make fetch a top level
// symbol of type string to native Promise('a)
// (where 'a is a variable type),
// and = "fetch" says in js-land, the name of this symbol is "fetch".
// we could change the name in the Reason side if we wanted to something
// else, e.g. reFetch
[@bs.val] external fetch: string => Js.Promise.t('a) = "fetch";

type stacLink = {
  href: string,
  rel: string,
};

let decodeStacLink = json =>
  Json.Decode.{
    href: json |> field("href", string),
    rel: json |> field("rel", string),
  };

type stacCollection = {
  stac_version: string,
  id: string,
  license: string,
  links: list(stacLink),
};

// this type could be inferred -- if I change stacCollection to something bogus like
// int, it won't say that it's getting a record type with certain fields back, it will
// understand that it's a stacCollection
// unfortunately this doesn't return any kind of either(e, a) -- there's a category theory
// library called bs-abstract that has an either type, but I'm not getting into that here
let decodeCollection: Js.Json.t => stacCollection =
  json =>
    Json.Decode.{
      stac_version: json |> field("stac_version", string),
      id: json |> field("id", string),
      license: json |> field("license", string),
      links: json |> field("links", list(decodeStacLink)),
    };

type state =
  | LoadingCollection
  | CollectionLoadError
  | LoadedCollection(stacCollection);

// a function called "make" with the [@react.component] decoration becomes a magic
// html tag style React thing with the name of whatever this file is called
// (see <SideBar> in Index.re)
[@react.component]
let make = () => {
  let (state, setState) = React.useState(() => LoadingCollection);

  // hooks! with numbers for how many values will be included in the effect
  React.useEffect0(() => {
    Js.Promise.(
      fetch(
        "http://localhost:9090/collections/e54a18e8-9992-47f3-923f-4adfe383f0dc",
      )
      |> then_(response => response##json())
      |> then_(jsonResponse => {
           setState(_previousState =>
             LoadedCollection(decodeCollection(jsonResponse))
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

  // Functions can also accept by-name arguments and can have their arguments
  // default to certain values. If you're only providing some named arguments,
  // you pass a () to tell ReasonML that you're done and it should just use the
  // defaults for the rest

  // since this jsx-looking thing is the last expression in this function, it's
  // returned (like Scala)
  <div
    style={ReactDOMRe.Style.make(
      ~background="coral",
      ~width="300px",
      ~overflow="auto",
      ~padding="0 15px 15px",
      ~height="100%",
      (),
    )}>
    // pattern matching
    {switch (state) {
     | LoadingCollection => React.string("Loading...")
     | CollectionLoadError =>
       React.string("Can't read collection from source, turn your server on")
     | LoadedCollection(collection) =>
       <div>
         <div>
           {React.string("License is: ")}
           {React.string(collection.license)}
         </div>
         <div>
           {React.string("Version is: ")}
           {React.string(collection.stac_version)}
         </div>
         <div>
           {React.string("Number of item is: ")}
           // Pizza operator :tada:
           // partial application on `filter` -- all functions have sugar and partial applicability
           // to consistency with js, so f(a, b) desugars to f(a)(b), but you never have to write
           // your partial applications by hand
           {React.string(
              collection.links
              |> List.filter(link => link.rel == "item")
              |> List.length
              |> string_of_int,
            )}
         </div>
       </div>
     }}
  </div>;
};