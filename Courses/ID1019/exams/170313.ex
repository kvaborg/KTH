defmodule Ten170313 do

  def freq(key, []) do [] end
  def freq(k, [{k, f} | t]) do
    [{k, f+1} | freq(k, t)]
  end
  def freq(key, [{k, f} | t]) do [{k, f} | freq(key, t)] end


end
