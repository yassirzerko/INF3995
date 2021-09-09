import React from "react";
import renderer from "react-test-renderer";
import { mount, shallow } from "enzyme";
import StickyHeadTable from "./DroneListTable";
import Paper from "@material-ui/core/Paper";
import Table from "@material-ui/core/Table";

describe("StickyHeadTable", () => {
  it("should render initial layout", () => {
    const component = shallow(<StickyHeadTable  />);
    expect(component.getElements()).toMatchSnapshot();
  });

  it("should render one Paper", () => {
    const component = shallow(<StickyHeadTable />);
    expect(component.find(Paper).length).toBe(1);
  });

  it("should render one Table", () => {
    const component = shallow(<StickyHeadTable />);
    expect(component.find(Table).length).toBe(1);
  });
});
