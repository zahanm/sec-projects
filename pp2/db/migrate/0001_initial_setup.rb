class InitialSetup < ActiveRecord::Migration
  def change
    create_table :users do |t|
      t.primary_key :id
      t.string :name, :null => false
      t.string :password, :null => false
      t.text :profile, :default => ''
      t.integer :zoobars, :default => 10
    end
  end
end
