/**
 * Represents the options for applying backpressure to a source sequence.
 */
type t =
  /**
   * Buffers all onNext values until the downstream consumes it.
   */
  | Buffer
  /**
   * Drops the most recent onNext value if the downstream can't keep up.
   */
  | Drop
  /**
   * Signals a Exceptions.MisisngBackpressure in case the downstream can't keep up.
   */
  | Error
  /**
   * Keeps only the latest onNext value, overwriting any previous value if the downstream can't keep up.
   */
  | Latest
  /**
   * OnNext events are written without any buffering or dropping.
   */
  | Missing
;

/**
 * Options to deal with buffer overflow when using onBackpressureBuffer.
 */
module Overflow {
  type t = 
    /**
     * Drop the latest value from the buffer.
     */
    | DropLatest
    /**
     * Drop the oldest value from the buffer.
     */
    | DropOldest
    /**
     * Signal a MissingBackpressureException and terminate the sequence.
     */
    | Error  
  ;
}