require 'active_record'
require 'uri'

db = URI.parse(ENV['DATABASE_URL'])

ActiveRecord::Base.establish_connection(
  :adapter =>  db.scheme == 'postgres' ? 'postgresql' : db.scheme,
  :host =>     db.host,
  :username => db.user,
  :password => db.password,
  :database => db.path[1..-1],
  :encoding => 'utf8'
)

class User < ActiveRecord::Base
  def transfer_to(user, amount)
    return false if !user or self == user

    transaction do
      self.reload
      user.reload

      return false if self.zoobars < amount

      self.zoobars -= amount
      user.zoobars += amount
      self.save!
      user.save!
      return true
    end
  end
end
