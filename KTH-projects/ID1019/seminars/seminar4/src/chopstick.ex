defmodule Chopstick do

  def start do
    stick = spawn_link(fn -> available() end) 
  end

  def available() do 
    receive do
      {:request, from} -> 
        send from, :granted
        gone() 
      :quit -> 
        :ok
      end
  end

  def gone() do
    receive do
      {:return, from} ->
        send from, :returned
        available() 
      :quit ->
        :ok
    end
  end

  def request(stick) do
    send stick, {:request, self()}
    receive do
      :granted ->
        :ok
    end
  end

   def return(stick) do
     send stick, {:return, self()}
     receive do
       :returned ->
         :ok
     end
   end

   def quit(stick) do
     send stick, :quit
   end

end
