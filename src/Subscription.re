type t('t) = {
  ..
  cancel: unit => unit
} as 't;

type s = t({
  .
  cancel: unit => unit
});
