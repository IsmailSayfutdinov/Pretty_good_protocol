if proto_pgp then return end  -- already loaded, skip

local proto_pgp = Proto("PGP", "Pretty Good Protocol")

local f_type = ProtoField.uint8("pgp.type", "Type", base.HEX)
local f_length = ProtoField.uint8("pgp.length", "Length", base.DEC)
local f_value = ProtoField.bytes("pgp.value", "Value")

proto_pgp.fields = { f_type, f_length, f_value }

function proto_pgp.dissector(buffer, pinfo, tree)
    pinfo.cols.protocol = "PGP"
    local subtree = tree:add(proto_pgp, buffer(), "Pretty Good Protocol")
    
    local i = 0
    while i < buffer:len() do
        local t = buffer(i, 1):uint()
        local l = buffer(i+1, 1):uint()
        
        subtree:add(f_type, buffer(i, 1))
        subtree:add(f_length, buffer(i+1, 1))
        subtree:add(f_value, buffer(i+2, l))
        
        i = i + 2 + l
    end
end

local udp_table = DissectorTable.get("udp.port")
udp_table:add(3333, proto_pgp)